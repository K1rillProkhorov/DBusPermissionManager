#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PERMISSION_SERVICE_NAME "com.system.permissions"
#define TIME_SERVICE_NAME "com.system.time"
#define DATABASE_NAME "permission.db"

enum eStatus
{
    Error = -1,
    Failure = 0,
    Success = 1
};

enum ePermissions { SystemTime = 0 };

#endif //DEFINITIONS_H
