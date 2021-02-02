#include <gb/gb.h>
#include <stdio.h>

//função para sincronizar os jogos
int wait_for_connection(){
    receive_byte();
    int out = 0,pad;
    while(!out){
        pad = joypad();
        if(pad == J_A || pad == J_B)
            out = 1;
    }
    if(pad == J_A){
        _io_out = pad;
        send_byte();
        while(_io_status == IO_SENDING){;}
        return 0;
    }
    
    if(pad == J_B){
        while(_io_status == IO_RECEIVING){;}
        return 1;
    }
}

void send_action(int action){
    _io_out = action;
    send_byte();
}

int validade_data(){
    if(_io_in == 0 || _io_in == 1)
        return _io_in;
    else
        return 3;
}