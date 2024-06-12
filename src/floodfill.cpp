#include <states.h>
#include <tof.h>
#include <position.h>
#include <maze.h>
// bool floodfillSearch()
// {
//     static int a = 0;
//     CODES c[14]= {MOVEMENT,MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION,
//                 MOVEMENT,INPLACE_ROTATION, MOVEMENT, MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION};
//     MODES m[14]= {FORWARDS,FORWARDS,LEFT,FORWARDS,LEFT,FORWARDS,LEFT,FORWARDS,FORWARDS,RIGHT,FORWARDS,RIGHT,FORWARDS,RIGHT};
//     setInstruction(c[a%14],m[a%14]);
//     a++;
//     return false;
// }

bool floodfillSearch()
{
    uint8_t centerX = SIZE / 2, centerY = SIZE / 2;
    coordenates center(centerX, centerY);
    floodfill(center);
    return false;
}
// Preencha matriz
void floodfill(coordenates center){
    getCell(center.getCoordenateX(), center.getCoordenateY());
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            setCell(i, j, 255);
        }
    }
    setCell(center.getCoordenateX(), center.getCoordenateY(), 0);
    // 255 255 255
    // 255  0  255
    // 255 255 255
    // Verifica as celulas entorno do centro, se não houver parede, atribui peso 1
    // A partir das celulas de peso 1, preencher com +1
}