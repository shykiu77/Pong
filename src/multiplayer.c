#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define NOT_OK 0 

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
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        return 0;
    }
    
    if(pad == J_B){
        while(_io_status == IO_RECEIVING){;}
        _io_out = 1;
        send_byte();
        while(_io_status == IO_SENDING){;}
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

int send_data(int *data,int num_dados){
    for(int i=0;i < num_dados; i++){
        _io_out = data[i];
        send_byte();
        while(_io_status == IO_SENDING){;}
        delay(1);
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        delay(1);
        if(_io_in != OK)
            return NOT_OK;
    }
    return OK;
}

int recieve_data(int*recieved, int num_dados){
    for(int i=0;i < num_dados; i++){
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        recieved[i] = _io_in;
        _io_out = OK;
        delay(1);
        send_byte();
        while(_io_status == IO_SENDING){;}
        delay(1);
    }
    return OK;
}