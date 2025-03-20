//
// Created by Arrun on 3/19/2025.
//

#include "cJSON.h"
#include "producer.h"
#include "consumer.h"
#include <stdlib.h>

void main(void) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", "test job");
    cJSON_AddStringToObject(json, "command", "ls");
    char *json_str = cJSON_Print(json);
    send_job_result(json_str, "job-queue");
    consume_jobs();
    exit(0);
}
