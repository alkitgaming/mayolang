#include <stdio.h>
#include <stdlib.h>
// new jar hello;
// open jar hello;
//     spread("hello ");
// close jar hello;
void hello()
{
    printf("hello ");
}    

// new jar world;
// open jar world;
//     spread("world!");
// close jar world;
void world()
{
    printf("world!");
}

// new jar addition;
//     made from miraclewhip one, miraclewhip two;
//     tastes like miraclewhip;
// open jar addition;
//     taste mix(one, two);
// close jar addition;

int addition(int one, int two)
{
    return one + two;
}

// hunger;
//     miraclewhip one is 5;
//     miraclewhip two is 10;
//     hello();
//     world();
//     spread(addition(one, two));
// full;
void main()
{
    int one = 5;
    int two = 10;
    hello();
    world();
    printf("%d", addition(one, two));
}