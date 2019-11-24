struct intpair {
        int a;
        int b;
};

program ADD_PROG {
        version ADD_VERS {
                int ADD(intpair) = 1;
                int SUB(intpair) = 2;
                int MULT(intpair) = 3;
                int DIV(intpair) = 4;

        } = 1;
        
} = 120180389;