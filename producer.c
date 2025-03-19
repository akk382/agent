//
// Created by Arrun on 3/19/2025.
//

#include <librdkafka/rdkafka.h>

void send_job_result(const char* job_result) {
    rd_kafka_t *rk;
    rd_kafka_conf_t *conf;
    rd_kafka_resp_err_t err;

    conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", "localhost:9092", NULL, 0);

    // Create Kafka producer
    rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, NULL, 0);
    conf = NULL;
    if (!rk) {
        fprintf(stderr, "Failed to create Kafka producer\n");
        exit(1);
    }

    err = rd_kafka_producev(
        rk,
        RD_KAFKA_V_TOPIC("job-results"),
        RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
        RD_KAFKA_V_VALUE(job_result, strlen(job_result)),
        RD_KAFKA_V_END);

    if (err != RD_KAFKA_RESP_ERR_NO_ERROR) {
        fprintf(stderr, "Failed to send job result: %s\n", rd_kafka_err2str(err));
    } else {
        printf("Job result sent successfully\n");
    }

    // Wait for messages to be delivered
    rd_kafka_flush(rk, 5000);
    rd_kafka_destroy(rk);
}
