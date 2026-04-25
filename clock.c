#include <stdbool.h>
#include<stdio.h> 
#include <time.h>
#include "raylib.h" 
#define WIDTH 1200 
#define HIGHT 600 
#define OFF_COLOR DARKGRAY
#define ON_COLOR RED
#define OFF_SET 40
#define SEGMENT_WIDTH  40
#define SEGMENT_THICKNESS 27
#define DIGIT_DISTANCE 140 
#define STARTING_POS 100
#define RADUIS 16
#define DOT_DISTANCE 100
void drawDot(Vector2 center, int seconds){
    DrawCircleV((Vector2){center.x, center.y - 50}, RADUIS, seconds%2 ? OFF_COLOR : ON_COLOR);
    DrawCircleV((Vector2){center.x, center.y + 50}, RADUIS, seconds%2 ? OFF_COLOR : ON_COLOR);
}
void drawSegment(Vector2 center, bool horizontal, Color color){
    int count = 6 ; 
    Vector2 a, b, c, d, e, f;
    if (horizontal) {
        a = (Vector2){center.x - SEGMENT_THICKNESS/2 - SEGMENT_WIDTH/2,center.y}; 
        b = (Vector2){center.x - SEGMENT_WIDTH/2 , center.y - SEGMENT_THICKNESS/2};
        c = (Vector2){center.x - SEGMENT_WIDTH/2 , center.y + SEGMENT_THICKNESS/2};
        d = (Vector2){center.x + SEGMENT_WIDTH/2 , center.y - SEGMENT_THICKNESS/2};
        e = (Vector2){center.x + SEGMENT_WIDTH/2 , center.y + SEGMENT_THICKNESS/2};
        f = (Vector2){center.x + SEGMENT_THICKNESS/2 + SEGMENT_WIDTH/2,center.y}; 
    }
    else {
        a = (Vector2){center.x, center.y - SEGMENT_THICKNESS/2 - SEGMENT_WIDTH/2};
        b = (Vector2){center.x + SEGMENT_THICKNESS/2, center.y -SEGMENT_WIDTH/2};
        c = (Vector2){center.x - SEGMENT_THICKNESS/2, center.y -SEGMENT_WIDTH/2};
        d = (Vector2){center.x + SEGMENT_THICKNESS/2, center.y +SEGMENT_WIDTH/2};
        e = (Vector2){center.x - SEGMENT_THICKNESS/2, center.y +SEGMENT_WIDTH/2};
        f = (Vector2){center.x, center.y + SEGMENT_THICKNESS/2 + SEGMENT_WIDTH/2};
    }
    Vector2 points [] ={a, c, b, e, d, f} ; 
    DrawTriangleStrip(points, count, color);
}
int digits[10][7]={
{1,1,1,0,1,1,1},//0
{0,0,1,0,0,1,0},// 1
{1,0,1,1,1,0,1},// 2
{1,0,1,1,0,1,1},// 3 
{0,1,1,1,0,1,0},// 4 
{1,1,0,1,0,1,1},// 5 
{1,1,0,1,1,1,1},// 6 
{1,0,1,0,0,1,0},// 7 
{1,1,1,1,1,1,1},// 8
{1,1,1,1,0,1,1} // 9
};
void drawDigit(Vector2 center, int digit){
    int *digits_segment = digits[digit];
    Vector2 first = {center.x, center.y - SEGMENT_WIDTH- OFF_SET};
    drawSegment(first, true, digits_segment[0] ? ON_COLOR : OFF_COLOR);
    Vector2 second = {center.x - SEGMENT_WIDTH/2 - OFF_SET/2, center.y - SEGMENT_WIDTH/2 - OFF_SET/2};
    drawSegment(second, false, digits_segment[1] ? ON_COLOR : OFF_COLOR);
    Vector2 third = {center.x + SEGMENT_WIDTH/2 + OFF_SET/2, center.y - SEGMENT_WIDTH/2 - OFF_SET/2};
    drawSegment(third, false, digits_segment[2] ? ON_COLOR : OFF_COLOR);
    Vector2 fourth = {center.x, center.y};
    drawSegment(fourth, true, digits_segment[3] ? ON_COLOR : OFF_COLOR);
    Vector2 fifth = {center.x - SEGMENT_WIDTH/2 - OFF_SET/2, center.y + SEGMENT_WIDTH/2 + OFF_SET/2};
    drawSegment(fifth, false, digits_segment[4] ? ON_COLOR : OFF_COLOR);
    Vector2 sixth = {center.x + SEGMENT_WIDTH/2 + OFF_SET/2, center.y + SEGMENT_WIDTH/2 + OFF_SET/2};
    drawSegment(sixth, false, digits_segment[5] ? ON_COLOR : OFF_COLOR);
    Vector2 seventh = {center.x, center.y + SEGMENT_WIDTH + OFF_SET};
    drawSegment(seventh, true, digits_segment[6] ? ON_COLOR : OFF_COLOR);
}
void drawTime(int hours, int min, int sec){
    drawDigit((Vector2){STARTING_POS,HIGHT/2},hours/10 );
    drawDigit((Vector2){STARTING_POS+DIGIT_DISTANCE, HIGHT/2}, hours%10);

    drawDot((Vector2){STARTING_POS+2*DIGIT_DISTANCE, HIGHT/2}, sec);    

    drawDigit((Vector2){STARTING_POS+3*DIGIT_DISTANCE, HIGHT/2}, min/10);
    drawDigit((Vector2){STARTING_POS+4*DIGIT_DISTANCE, HIGHT/2}, min%10);

    drawDot((Vector2){STARTING_POS+5*DIGIT_DISTANCE, HIGHT/2}, sec);

    drawDigit((Vector2){STARTING_POS+6*DIGIT_DISTANCE, HIGHT/2}, sec/10);
    drawDigit((Vector2){STARTING_POS+7*DIGIT_DISTANCE, HIGHT/2}, sec%10);

}
int main(int argc, char *argv[])
{
    InitWindow(WIDTH , HIGHT , "Digital Clock");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        time_t  current_time= time(NULL);
        struct tm* current_local_time = localtime(&current_time);
        drawTime(current_local_time->tm_hour, current_local_time->tm_min, current_local_time->tm_sec);
        EndDrawing();
    }
    return 0;
}
