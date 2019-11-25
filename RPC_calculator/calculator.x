#define LEN_CMD 128
struct CMD_INPUT {
        char cmd_input[LEN_CMD];
};

program CALC {
        version CALC_VERS {
                int CALCULATION(CMD_INPUT) = 1;
        } = 1;

        
} = 120180389;