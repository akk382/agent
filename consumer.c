//
// Created by Arrun on 3/18/2025.
//

#include <librdkafka/rdkafka.h>
#include "execute_job.h"
#include <stdlib.h>

void consume_jobs() {
    rd_kafka_t *rk; // Kafka handle
    rd_kafka_conf_t *conf; // Kafka configuration
    rd_kafka_resp_err_t err;

    // Kafka consumer configuration
    conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "group.id", "agent-group", NULL, 0);
    rd_kafka_conf_set(conf, "bootstrap.servers", "broker:9092", NULL, 0);

    // Create Kafka consumer
    rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, NULL, 0);
    conf = NULL;
    if (!rk) {
        fprintf(stderr, "Failed to create Kafka consumer\n");
        exit(1);
    }

    // Subscribe to the topic
    rd_kafka_topic_partition_list_t *topics;
    topics = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(topics, "job-queue", RD_KAFKA_PARTITION_UA);
    rd_kafka_subscribe(rk, topics);

    printf("Listening for the jobs...\n");

    // Polling loop to consume the messages
    while (1) {
        rd_kafka_message_t *msg = rd_kafka_consumer_poll(rk, 1000);
        if (msg) {
            if (msg->err) {
                fprintf(stderr, "Consumer error: %s\n", rd_kafka_message_errstr(msg));
            } else {
                printf("Received job: %.*s\n", (int)msg->len, (char*)msg->payload);
                process_job((char*)msg->payload);
                // TODO: Process the job and execute commands
            }
            rd_kafka_message_destroy(msg);
        }
    }

    // Cleanup
    rd_kafka_consumer_close(rk);
    rd_kafka_destroy(rk);
}