#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim){

    std::size_t boardSize {xdim*ydim};

    char * board_array { new char[boardSize] {} };

    return board_array;
}


void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){

    std::size_t pos{};

    for (std::size_t y{0}; y < ydim; ++y){
        for (std::size_t x{0}; x < xdim; ++x){
            pos = x + y*xdim;

            if ( (board[pos] & valueMask()) == 9 ){
                if ( y == 0 ){ //Top row
                    if ( x == 0){ //left side

                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos+xdim] != 9){
                            board[pos+xdim]++;
                        }
                        if (board[pos+xdim+1] != 9){
                            board[pos+xdim+1]++;
                        }
                    }
                    else if ( x == xdim -1 ){ //ride side

                        if (board[pos-1] != 9){
                            board[pos-1]++;
                        }
                        if (board[pos+xdim] != 9){
                            board[pos+xdim]++;
                        }
                        if (board[pos+xdim+1]  != 9){
                            board[pos+xdim-1]++;
                        } 
                    }
                    else { //top middle

                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos+xdim] != 9){
                            board[pos+xdim]++;
                        }
                        if (board[pos+xdim+1] != 9){
                            board[pos+xdim+1]++;
                        }
                        if (board[pos-1] != 9){
                            board[pos-1]++;
                        }
                        if (board[pos+xdim-1]!= 9){
                            board[pos+xdim-1]++;
                        }
                    }
                }
                else if ( y == ydim-1 ){ //bottom row
                    if ( x == 0 ){ //right side

                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos-xdim]  != 9){
                            board[pos-xdim]++;
                        }
                        if (board[pos-xdim+1] != 9){
                            board[pos-xdim+1]++;
                        }
                    }
                    else if ( x == xdim - 1 ){ //left side

                        if (board[pos-1] != 9){
                            board[pos-1]++;
                        }
                        if (board[pos-xdim] != 9){
                            board[pos-xdim]++;
                        }
                        if (board[pos-xdim-1] != 9){
                            board[pos-xdim-1]++;
                        }
                    }
                    else{ //bottom middle

                        if (board[pos-1]  != 9){
                            board[pos-1]++;
                        }
                        if (board[pos-xdim]  != 9){
                            board[pos-xdim]++;
                        }
                        if (board[pos-xdim-1] != 9){
                            board[pos-xdim-1]++;
                        }
                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos-xdim+1] != 9){
                            board[pos-xdim+1]++;
                        }
                    }
                }
                else{ //middle rows

                    if (board[pos-xdim] != 9){
                        board[pos-xdim]++;
                    }
                    if (board[pos+xdim]  != 9){
                        board[pos+xdim]++;
                    }
                    if ( x == 0 ){ //right side

                        if (board[pos-xdim+1]  != 9){
                            board[pos-xdim+1]++;
                        }
                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos+xdim+1] != 9){
                            board[pos+xdim+1]++;
                        }
                    }
                    else if ( x == xdim - 1 ){ //left side

                        if (board[pos-xdim-1] != 9){
                            board[pos-xdim-1]++;
                        }
                        if (board[pos-1] != 9){
                            board[pos-1]++;
                        }
                        if (board[pos+xdim-1] != 9){
                            board[pos+xdim-1]++;
                        }
                    }
                    else{ //middle

                        if (board[pos-xdim-1] != 9){
                            board[pos-xdim-1]++;
                        }
                        if (board[pos-1] != 9){
                            board[pos-1]++;
                        }
                        if (board[pos+xdim-1]  != 9){
                            board[pos+xdim-1]++;
                        }
                        if (board[pos-xdim+1] != 9){
                            board[pos-xdim+1]++;
                        }
                        if (board[pos+1] != 9){
                            board[pos+1]++;
                        }
                        if (board[pos+xdim+1] != 9){
                            board[pos+xdim+1]++;
                        }    

                    }
                }
            }

        }
    }
}


void hideBoard(char * board, std::size_t xdim, std::size_t ydim){

    std::size_t boardSize {xdim*ydim};

    for (std::size_t i{0}; i < boardSize; ++i){
        board[i] = board[i] | hiddenBit();
    }

}


void cleanBoard(char * board){

    delete[] board;
    board = nullptr;

}


void printBoard(char * board, std::size_t xdim, std::size_t ydim){

    std::size_t boardSize {xdim*ydim};

    if ( (xdim == 0) || (ydim == 0)){
        return;
    }

    for (std::size_t i{0}; i < ydim; ++i){
        for (std::size_t j{0}; j < xdim; ++j){

            if ( (board[j + i*xdim] & hiddenBit()) > 0){ 
                if ( (board[j + i*xdim] & markedBit()) > 0){
                    std::cout << "M";
                }
                else{
                    std::cout << "*";
                }
            }
            else {
                std::cout << (board[j + i*xdim] & valueMask());
            }

        }
        std::cout << std::endl;
    }

}


int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    std::size_t pos{xloc + yloc*xdim};

    if ( board[pos] & valueMask() == 9){
        return 9;
    }
    else if ( (board[pos] & markedBit()) > 0){
        return 1;
    }
    else if ( ((board[pos] & hiddenBit()) == 0) ){
        return 2;
    }



    board[pos] = board[pos] ^ hiddenBit();
    

    if ( (board[pos] & valueMask()) == 0 ){

        if ( yloc == 0 ){ //Top row
            if ( xloc == 0){ //left side


                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                } 
                if ( (board[pos+xdim] & hiddenBit()) > 0 ){
                    board[pos+xdim] = board[pos+xdim] ^ hiddenBit();
                } 
                if ( (board[pos+xdim+1] & hiddenBit()) > 0 ){
                    board[pos+xdim+1] = board[pos+xdim+1] ^ hiddenBit();
                }             

            }
            else if ( xloc == xdim -1 ){ //right side
 

                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                }
                if ( (board[pos+xdim] & hiddenBit()) > 0 ){
                    board[pos+xdim] = board[pos+xdim] ^ hiddenBit();
                } 
                if ( (board[pos+xdim-1] & hiddenBit()) > 0 ){
                    board[pos+xdim-1] = board[pos+xdim-1] ^ hiddenBit();
                }                 

                 
            }
            else { //top middle


                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                }
                if ( (board[pos+xdim] & hiddenBit()) > 0 ){
                    board[pos+xdim] = board[pos+xdim] ^ hiddenBit();
                } 
                if ( (board[pos+xdim+1] & hiddenBit()) > 0 ){
                    board[pos+xdim+1] = board[pos+xdim+1] ^ hiddenBit();
                }  
                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                }
                if ( (board[pos+xdim-1] & hiddenBit()) > 0 ){
                    board[pos+xdim-1] = board[pos+xdim-1] ^ hiddenBit();
                }    

                
            }
        }
        else if ( yloc == ydim-1 ){ //bottom row
            if ( xloc == 0 ){ //left side


                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                }
                if ( (board[pos-xdim] & hiddenBit()) > 0 ){
                    board[pos-xdim] = board[pos-xdim] ^ hiddenBit();
                } 
                if ( (board[pos-xdim+1] & hiddenBit()) > 0 ){
                    board[pos-xdim+1] = board[pos-xdim+1] ^ hiddenBit();
                }  

                        
            }
            else if ( xloc == xdim - 1 ){ //right side



                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                }
                if ( (board[pos-xdim] & hiddenBit()) > 0 ){
                    board[pos-xdim] = board[pos-xdim] ^ hiddenBit();
                } 
                if ( (board[pos-xdim-1] & hiddenBit()) > 0 ){
                    board[pos-xdim-1] = board[pos-xdim-1] ^ hiddenBit();
                }  

                      
            }
            else{ //bottom middle


                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                }
                if ( (board[pos-xdim] & hiddenBit()) > 0 ){
                    board[pos-xdim] = board[pos-xdim] ^ hiddenBit();
                } 
                if ( (board[pos-xdim-1] & hiddenBit()) > 0 ){
                    board[pos-xdim-1] = board[pos-xdim-1] ^ hiddenBit();
                }  
                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                }
                if ( (board[pos-xdim+1] & hiddenBit()) > 0 ){
                    board[pos-xdim+1] = board[pos-xdim+1] ^ hiddenBit();
                }  

                        
            }
        }
        else{ //middle rows


            if ( (board[pos-xdim] & hiddenBit()) > 0 ){
                board[pos-xdim] = board[pos-xdim] ^ hiddenBit();
            }
            if ( (board[pos+xdim] & hiddenBit()) > 0 ){
                board[pos+xdim] = board[pos+xdim] ^ hiddenBit();
            } 

          
            if ( xloc == 0 ){ //left side
  

                if ( (board[pos-xdim+1] & hiddenBit()) > 0 ){
                    board[pos-xdim+1] = board[pos-xdim+1] ^ hiddenBit();
                }
                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                } 
                if ( (board[pos+xdim+1] & hiddenBit()) > 0 ){
                    board[pos+xdim+1] = board[pos+xdim+1] ^ hiddenBit();
                }  

            
            }
            else if ( xloc == xdim - 1 ){ //right side


                if ( (board[pos-xdim-1] & hiddenBit()) > 0 ){
                    board[pos-xdim-1] = board[pos-xdim-1] ^ hiddenBit();
                }
                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                } 
                if ( (board[pos+xdim-1] & hiddenBit()) > 0 ){
                    board[pos+xdim-1] = board[pos+xdim-1] ^ hiddenBit();
                }  

                
            }
            else{ //middle


                if ( (board[pos-xdim+1] & hiddenBit()) > 0 ){
                    board[pos-xdim+1] = board[pos-xdim+1] ^ hiddenBit();
                }
                if ( (board[pos+1] & hiddenBit()) > 0 ){
                    board[pos+1] = board[pos+1] ^ hiddenBit();
                } 
                if ( (board[pos+xdim+1] & hiddenBit()) > 0 ){
                    board[pos+xdim+1] = board[pos+xdim+1] ^ hiddenBit();
                }  
                if ( (board[pos-xdim-1] & hiddenBit()) > 0 ){
                    board[pos-xdim-1] = board[pos-xdim-1] ^ hiddenBit();
                }
                if ( (board[pos-1] & hiddenBit()) > 0 ){
                    board[pos-1] = board[pos-1] ^ hiddenBit();
                } 
                if ( (board[pos+xdim-1] & hiddenBit()) > 0 ){
                    board[pos+xdim-1] = board[pos+xdim-1] ^ hiddenBit();
                }  


            }
        }

    
 
    }

    return 0;
}


int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    std::size_t position{xloc + yloc*xdim};

    board[position] = board[position] ^ markedBit(); 


    if ( (board[position] & hiddenBit()) > 0 ){
        return 0;
    }
    else{
        return 2;
    }

}


bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){

    std::size_t boardSize{xdim*ydim};


    for (int i{0}; i < boardSize; ++i){
        if ( (board[i] & hiddenBit() > 0) || (board[i] & markedBit()) > 0 ){
            if ( (board[i] & valueMask()) != 9){
                return false;
            }
        }   
  
    }

    
    return true;
    
}

