#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point_instance
{
    float x,y;
    char str_rep[20];
} point_instance;

typedef struct point_class
{
    point_instance* (*constructor)(float, float);
    point_instance* (*cpy_constructor)(const point_instance*);
    void (*destructor)(void**);

    const char* (*to_string)(struct point_instance*);
} point_class;


point_instance* pb_constructor(float x, float y)
{
    point_instance* point = (point_instance*)calloc(1, sizeof(point_instance));
    if(point)
    {
        point->x = x;
        point->y = y;
        const char empty[20] = {0};
        strcpy(point->str_rep, empty);
    }
    return point;
}

point_instance* pb_cpy_constructor(const point_instance* rhs)
{
    if(!rhs) return 0;

    point_instance* point = pb_constructor(rhs->x, rhs->y);

    return point;
}

void pb_destructor(void** instance)
{
    if(!instance || !*instance) return;
    free((point_instance*)(*instance));
    *instance = 0;
}

const char* pb_to_string(point_instance* point)
{
    if(!point) return "";

    sprintf(point->str_rep, "(%.2f,%.2f)", point->x, point->y);
    return (point->str_rep);
}

void delete(void** instance, void(*destructor)(void** type_instance))
{
    destructor(instance);
}

static point_class Point = {&pb_constructor, &pb_cpy_constructor, &pb_destructor, &pb_to_string};
typedef point_instance* point;

point new_Point(float x, float y)
{
    point instance = Point.constructor(x,y);
    return instance;
}

point cpy_Point(const point rhs)
{
    point instance = Point.cpy_constructor(rhs);
    return instance;
}

int main(void)
{
    point p1 = new_Point(1,1);
    printf("%s\n", Point.to_string(p1));
    point p2 = cpy_Point(p1);
    printf("%s\n", Point.to_string(p2));

    p2->x = 27;
    p2->y = 12;

    printf("%s\n", Point.to_string(p2));

    delete((void*)&p1, Point.destructor);

    printf("%p\n", p1);
    return 0;
}