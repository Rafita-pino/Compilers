int  main (){

#define FACTORIAL(x) ((x) == 0 ? 1 : (x) * (FACTORIAL((x)-1)))

}


FACTORIAL(3)


((3) == 0 ? 1 : (3) * (FACTORIAL((3)-1)))



((3) == 0 ? 1 : (3) * ((2) == 0 ? 1 : (2) * (FACTORIAL((2)-1))))





((3) == 0 ? 1 : (3) * ((2) == 0 ? 1 : (2) * (FACTORIAL((2)-1)))) == 0 ? 1 : (1) * (FACTORIAL((1)-1))
((3) == 0 ? 1 : (3) * ((2) == 0 ? 1 : (2) * (FACTORIAL((2)-1)))) == 0 ? 1 : (1) * (FACTORIAL((1)-1))