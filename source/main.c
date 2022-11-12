#include <tonc.h>
#include <string.h>
#include "draw.h"

#include "ride.h"
#include "mcride.h"


#define screenwidth 240
#define screenheight 160

OBJ_ATTR mysprite;

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

int main(void) {
	
	int x= 96, y= 32;
    
	OBJ_ATTR *metr= &obj_buffer[0];
    
	obj_set_attr(metr, 
        ATTR0_SQUARE,              	// Square, regular sprite
        ATTR1_SIZE_64,              // 64x64p, 
        ATTR2_PALBANK(0) | 0);   	// palbank 0, tile 0
	
	REG_DISPCNT= DCNT_MODE0 | DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2;		//set the screen to mode 3, enable object layer
	dma_cpy(MEM_VRAM_OBJ, mcrideTiles, 512, 1, DMA_32 | DMA_ENABLE);	// put image in VRAM, enable DMA
	dma_cpy(MEM_PAL_OBJ, mcridePal, 256, 1, DMA_16 | DMA_ENABLE);		// send sprite palette to object palette RAM
	obj_set_pos(metr, x, y);
	while (1) {
	    vid_vsync();
	    //memset32(MEM_VRAM, 0, 19200 );	//clear the screen
        key_poll();
		
		if(key_is_down(KEY_UP)){
			y +=1;
		}

        //metr->attr2= ATTR2_BUILD(0, 0, 0);
        obj_set_pos(metr, x, y);			
		oam_copy(oam_mem, obj_buffer, 1);   // (6) Update OAM (only one now)
	}
	
}