#include <gb/gb.h>
#include <stdio.h>
int wait_for_connection(){
    receive_byte();
    int out = 0,pad;
    while(!out){
        pad = joypad();
        if(pad == J_A || pad == J_B)
            out = 1;
    }
    if(pad == J_A){
        send_byte();
        while(_io_status == IO_SENDING){;}
        return 1;
    }
    
    if(pad == J_B){
        while(_io_status == IO_RECEIVING){;}
        return 2;
    }
}