//
// Created by Arrun on 3/17/2025.
//

/*
 * 1. Should run linux commands -- InProgress
 * 2. Should run linux programs
 * 3. Should execute shell scripts
 * 4. Should execute python scripts
 * 5. Should run java programs
 */

#include "execute_job.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>

void process_job(char* job_payload) {
    cJSON *json = cJSON_Parse(job_payload);
    if (json == NULL) {
        const char *err = cJSON_GetErrorPtr();
        if (err != NULL) {
            printf("Error: %s\n", err);
        }
        cJSON_Delete(json);
        exit(1);
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *command = cJSON_GetObjectItemCaseSensitive(json, "command");

    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("Job Name: %s\n", name->valuestring);
    }
    if (cJSON_IsString(command) && command->valuestring != NULL) {
        printf("Command: %s\n", command->valuestring);
    }


}