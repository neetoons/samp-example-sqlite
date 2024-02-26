#include <a_samp>

#define PLAYER_DEFAULT_POS_X    1742.8944
#define PLAYER_DEFAULT_POS_Y    -1860.5548
#define PLAYER_DEFAULT_POS_Z    13.5786

new DB:db_handle;

#include "core/playerdata"
#include "core/database/functions"

public OnGameModeInit()
{
    db_handle = DB:db_open("database.db");
    if(db_handle == DB:0)
    {
        print("No se dio la conexion a \"database.db\"");
        SendRconCommand("exit");
    }
    else
    {
        print("conexion exitosa a \"database.db\"");

        new DBResult:db_result;
        new sql[1000] = 
            "CREATE TABLE IF NOT EXISTS users(      \
                `id` INTEGER UNIQUE NOT NULL,       \
                `name` VARCHAR(25) UNIQUE NOT NULL, \
                `pos_x` FLOAT DEFAULT 1743.8944,    \
                `pos_y` FLOAT DEFAULT -1859.5548,   \
                `pos_z` FLOAT DEFAULT 13.5786,      \
                PRIMARY KEY(`id` AUTOINCREMENT)     \
            );"
        ;
        db_result = db_query(db_handle, sql);

        if(db_result)
        {
            print("sql de la base de datos sin errores");
        }
        else
        {
            print("Hay un error en la sintaxis sql, posiblemente no se guarden los datos");
            SendRconCommand("exit");
        }
        db_free_result(db_result);

    }
    return 1;
}
//------------------------------------------------
public OnGameModeExit()
{
    db_close(db_handle);
    return 1;
}
//------------------------------------------------
public OnPlayerConnect(playerid)
{
    login(playerid);
    return 1;
}
//------------------------------------------------
public OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    SavePlayerPos(playerid);
    return 1;
}

public OnPlayerSpawn(playerid)
{
    SetPlayerPos(playerid, 
        PlayerData[playerid][p_pos_x], 
        PlayerData[playerid][p_pos_y], 
        PlayerData[playerid][p_pos_z]
    );
    return 1;
}

main()
{
    print("Gamemode iniciada");
}