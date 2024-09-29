#ifndef DEFINITIONS_H
#define DEFINITIONS_H

constexpr auto SERVICE_NAME = "com.system.permissions";
constexpr auto DATABASE_NAME = "permission.db";

enum eStatus
{
    Error = -1,
    Failure = 0,
    Success = 1
};

enum ePermissions { SystemTime = 0 };

#endif //DEFINITIONS_H
