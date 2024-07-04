#include <iostream>
#include <sqlite3.h>

void createDatabase() {
    sqlite3* DB;
    int exit = sqlite3_open("ejemplo.db", &DB);

    if (exit) {
        std::cerr << "Error al abrir DB " << sqlite3_errmsg(DB) << std::endl;
        return;
    } else {
        std::cout << "Base de datos creada exitosamente" << std::endl;
    }
    sqlite3_close(DB);
}

void createTable() {
    sqlite3* DB;
    char* messageError;

    std::string sql = "CREATE TABLE PERSONA("
                      "ID INT PRIMARY KEY NOT NULL, "
                      "NOMBRE TEXT NOT NULL, "
                      "EDAD INT NOT NULL, "
                      "DIRECCION CHAR(50), "
                      "SALARIO REAL);";

    int exit = sqlite3_open("ejemplo.db", &DB);

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al crear tabla" << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
    sqlite3_close(DB);
}

void insertData() {
    sqlite3* DB;
    char* messageError;

    std::string sql = "INSERT INTO PERSONA (ID, NOMBRE, EDAD, DIRECCION, SALARIO) "
                      "VALUES (1, 'Paula', 32, 'San Jose', 20000.00);";

    int exit = sqlite3_open("ejemplo.db", &DB);

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al insertar registro" << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Registro creado correctamente" << std::endl;
    }
    sqlite3_close(DB);
}

void selectData() {
    sqlite3* DB;
    sqlite3_stmt* stmt;

    int exit = sqlite3_open("ejemplo.db", &DB);

    std::string sql = "SELECT * FROM PERSONA;";

    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

    if (exit != SQLITE_OK) {
        std::cerr << "Error en seleccion" << std::endl;
        return;
    }

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "ID: " << sqlite3_column_text(stmt, 0) << std::endl;
        std::cout << "NOMBRE: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "EDAD: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << "DIRECCION: " << sqlite3_column_text(stmt, 3) << std::endl;
        std::cout << "SALARIO: " << sqlite3_column_text(stmt, 4) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

int main() {

    createDatabase();
    createTable();
    insertData();
    selectData();

    return 0;
}
