#include "timer.h"
#include "matrix.h"
#include "debug.h"
#include "wait.h"
#include <print.h>
#include "platforms/chibios/gpio.h"
#include "i2c_master.h"

#define MCP23017_I2C_BASE_ADDRESS 0x20
#define MCP23017_A0 0x01
#define MCP23017_A1 0x02
#define MCP23017_A2 0x04

#define MCP23017_IODIR_A 0x00
#define MCP23017_IODIR_B 0x01
#define MCP23017_GPIO_A 0x12
#define MCP23017_GPIO_B 0x13
#define MCP23017_IOCON_BANK0 0x0A
#define MCP23017_IOCON_BANK1 0x05

#define REGISTER_MODE_READ 1
#define REGISTER_MODE_WRITE 2

#define MCP23017_I2C_TIMEOUT 100

i2c_status_t mcp23017_i2c_rw_register(uint8_t addrpin, uint8_t regaddr, uint8_t *data, uint8_t mode);

uint8_t COL_BITS[] = {
    1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, // left
    1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5  // right
};
uint8_t ROW_BITS[] = { 1, 1 << 1, 1 << 2, 1 << 3};

uint8_t COL_ADDRESS_MAPPING[] = {
                                    MCP23017_A0, MCP23017_A0, MCP23017_A0, MCP23017_A0, MCP23017_A0, MCP23017_A0,
                                    MCP23017_A1, MCP23017_A1, MCP23017_A1, MCP23017_A1, MCP23017_A1, MCP23017_A1
                                };

uint8_t MCP23017_ADDRESS_SET[] = {MCP23017_A1, MCP23017_A0};

void matrix_init_custom(void) {
    i2c_init();
    wait_ms(10);

    int i2c_num = sizeof(MCP23017_ADDRESS_SET);
    // BANK0ICON設定（念のため）
    uint8_t iocon = 0x00;
    // GPIOAをInputに設定
    uint8_t iodir_a  = 0xff;
    // GPIOBをOutputに設定
    uint8_t iodir_b  = 0x00;

    for(int counter = 0; counter < i2c_num; counter++) {
        mcp23017_i2c_rw_register(MCP23017_ADDRESS_SET[counter], MCP23017_IOCON_BANK0, &iocon,REGISTER_MODE_WRITE);
        mcp23017_i2c_rw_register(MCP23017_ADDRESS_SET[counter], MCP23017_IOCON_BANK1, &iocon,REGISTER_MODE_WRITE);
        mcp23017_i2c_rw_register(MCP23017_ADDRESS_SET[counter], MCP23017_IODIR_A, &iodir_a, REGISTER_MODE_WRITE);
        mcp23017_i2c_rw_register(MCP23017_ADDRESS_SET[counter], MCP23017_IODIR_B, &iodir_b, REGISTER_MODE_WRITE);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t scaned_matrix[sizeof(ROW_BITS)];
    memset(scaned_matrix, 0, sizeof(scaned_matrix));

    int col_num = sizeof(COL_BITS);
    int row_num = sizeof(ROW_BITS);

    for (int col = 0; col < col_num; col++) {
        // MCP23017側のMatrix
        // COL側、特定のCOLだけHIGHにして、他はLOWにする
        uint8_t write_buf = COL_BITS[col];
        uint8_t addrpin = COL_ADDRESS_MAPPING[col];
        i2c_status_t status = mcp23017_i2c_rw_register(addrpin, MCP23017_GPIO_B, &write_buf,REGISTER_MODE_WRITE);

        if (status != I2C_STATUS_SUCCESS) {
            // return 0;
        }

        // ROW側、読み取り
        uint8_t read_buf;
        status = mcp23017_i2c_rw_register(addrpin, MCP23017_GPIO_A, &read_buf, REGISTER_MODE_READ);

        if (status != I2C_STATUS_SUCCESS) {
            // return 0;
        }

        for (int row = 0; row < row_num; row++) {
            if (read_buf & ROW_BITS[row]) {
                scaned_matrix[row] |= 1 << col;
            }
        }
    }


    bool updated = false;
    for (int row = 0; row < row_num; row++) {
        if (current_matrix[row] != scaned_matrix[row]) {
            current_matrix[row] = scaned_matrix[row];
            updated = true;
        }
    }

    return updated;
}

i2c_status_t mcp23017_i2c_rw_register(uint8_t addrpin, uint8_t regaddr, uint8_t *data, uint8_t mode) {
    uint8_t address = MCP23017_I2C_BASE_ADDRESS;
    address |= addrpin;
    i2c_status_t status = -1;
    if(mode == REGISTER_MODE_READ) {
        status = i2c_read_register(address << 1, regaddr, data, 1, MCP23017_I2C_TIMEOUT);
    }
    else if(mode == REGISTER_MODE_WRITE) {
        status = i2c_write_register(address << 1, regaddr, data, 1, MCP23017_I2C_TIMEOUT);
    }
    return status;
}
