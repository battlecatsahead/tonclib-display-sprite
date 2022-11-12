#include "tonc.h"
void drawline(int x1, int y1, int x2, int y2) {
    int x,y,dx,dy,e;
    int xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;
    if(x1<x2)
        xinc=1;
    else
        xinc=-1;
    if(y1<y2)
        yinc=1;
    else
        yinc=-1;
    x=x1;
    y=y1;
    if(dx>=dy)   
    {
        e=(2*dy)-dx;
        while(x!=x2)
        {
            if(e<0)
                e=e+(2*dy);
            else
            {
                e=e+(2*(dy-dx));
                y=y+yinc;
            }
            x=x+xinc;
            m3_plot( x, y, RGB15(31, 0, 0) );
        }
    }
    else
    {
        e=(2*dx)-dy;
        while(y!=y2)
        {
            if(e<0)
                e=e+(2*dx);
            else
            {
                e=e+(2*(dx-dy));
                x=x+xinc;
            }
            y=y+yinc;
            m3_plot( x, y, RGB15(31, 0, 0) );
        }
    }
}

void drawsquare(int x, int y, int size){
    drawline(x + size, y + size, x + size, y - size);
}

void plotxy(int x, int y, int col1, int col2, int col3){
    m3_plot( x, y, RGB15(col1, col2, col3) );
}