login(playerid)
{
    GetPlayerName(playerid, PlayerData[playerid][p_name], MAX_PLAYER_NAME);

    new DBResult:db_result;
    new sql[] = "SELECT * FROM `users` WHERE `name` = '%s' LIMIT 1";
    new query[sizeof sql + MAX_PLAYER_NAME];
    format(query, sizeof query, sql, PlayerData[playerid][p_name]);
    printf("%s", query);
    db_result = db_query(db_handle, query);

    // el jugador existe en base de datos
    if (db_num_rows(db_result))
    {
        SendClientMessage(playerid, -1, "Bienvenido/a de regreso");
        PlayerData[playerid][p_pos_x] = db_get_field_assoc_float(db_result, "pos_x");
        PlayerData[playerid][p_pos_y] = db_get_field_assoc_float(db_result, "pos_y");
        PlayerData[playerid][p_pos_z] = db_get_field_assoc_float(db_result, "pos_z");
    }
    // el jugador no existe en base de datos
    else
    {
        SendClientMessage(playerid, -1, "No estas registrado/a, vamos a registrarte");
        PlayerData[playerid][p_pos_x] = PLAYER_DEFAULT_POS_X;
        PlayerData[playerid][p_pos_y] = PLAYER_DEFAULT_POS_Y;
        PlayerData[playerid][p_pos_z] = PLAYER_DEFAULT_POS_Z;
        Register(playerid);
    }
    db_free_result(db_result);
}
//------------------------------------------------
Register(playerid)
{
    new DBResult:db_result;
    new query[300];
    new sql[] = "INSERT INTO `users`(name) VALUES('%s');";
    format(query, sizeof query, sql, PlayerData[playerid][p_name]);
    printf("%s", query);
    db_result = db_query(db_handle, query);

    // DEBUGGING
    if (db_result)
    {
        printf("se guardaron los datos de %s", PlayerData[playerid][p_name]);
    }
    else
    {
        printf("No se guardaron los datos de %s", PlayerData[playerid][p_name]);
    }
    db_free_result(db_result);
}

SavePlayerPos(playerid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    new query[300];
    new sql[] =
        "UPDATE `users` SET \
        `pos_x` = %f,        \
        `pos_y` = %f,        \
        `pos_z` = %f         \
        WHERE `name` = '%s';";
    format(query, sizeof query, sql, x, y, z, PlayerData[playerid][p_name]);
    printf("%s", query);
    db_free_result(db_query(db_handle, query));
}