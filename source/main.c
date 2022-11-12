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
	oam_init(obj_buffer,128);

	int x= 96, y= 32;
    int i = 0;
	OBJ_ATTR *mysprite= &obj_buffer[0];
    
	obj_set_attr(mysprite, 
        ATTR0_8BPP | ATTR0_SQUARE,              	// Square, regular sprite
        ATTR1_SIZE_64,              // 64x64p, 
        ATTR2_PRIO (0));   	// palbank 0, tile 0
	
	REG_DISPCNT= DCNT_MODE0 | DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2;		// set the screen to mode 3, enable object layer
	//hide any sprites already on screen
	;
	dma_cpy(MEM_VRAM_OBJ, mcrideTiles, 1024, 1, DMA_32 | DMA_ENABLE);	// put image in VRAM, enable DMA
	dma_cpy(MEM_PAL_OBJ, mcridePal, 256, 1, DMA_16 | DMA_ENABLE);		// send sprite palette to object palette RAM

	//memcpy(VRAM_BG_SIZE, rideBitmap, rideBitmapLen);					// send background image to VRAM

	obj_set_pos(mysprite, x, y);

		for(i = 1; i < 128; i++){
			obj_set_attr(&obj_buffer[i],         	
    	    ATTR0_SHAPE(1111),
			ATTR1_X(1),              
        	ATTR2_PALBANK(-256));
		}

	while (1) {
	    vid_vsync();
	    //memset32(MEM_VRAM, 0, 19200 );	//clear the screen
        

		key_poll();
		
		if(key_is_down(KEY_UP)){
			y +=1;
		}

        //metr->attr2= ATTR2_BUILD(0, 0, 0);
        obj_set_pos(mysprite, x, y);		
		//oam_copy(oam_mem, obj_buffer, 1);	// (6) Update OAM (only one now)
		
		oam_copy(oam_mem, obj_buffer, 1);	   
		
	}
	
}