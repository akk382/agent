
 1. Should run linux commands -- InProgress
 2. Should run linux programs
 3. Should execute shell scripts
 4. Should execute python scripts
 5. Should run java programs


1. Should run linux commands - InProgress
   1. Take the command name, args
   2. If it's a full path from root and if the file is executable, execute it.
   3. If it's a full path from root and if the file is not executable, throw error.
   4. If it's not a full path and is a relative path, do the same as above.
   5. If it's just a name, then search the path for the executables, if found execute it.
   6. If not found throw error
   7. Save the stdout and stderr to log files
   8. Save the return code of the process to a file (for now), should be reported back the agent manager and save it to db).

2. Should run linux programs - TODO





### Job Structure:
```json
{
   "name": "Job Name",
   "command": "Job",
   // "path": "If command is null"
}
```