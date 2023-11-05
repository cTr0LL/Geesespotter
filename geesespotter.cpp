#include "geesespotter_lib.h"
#include <iostream>

char * create_board(std::size_t x_dim, std::size_t y_dim)
{
    char *board=new char[x_dim*y_dim];
    return board;
}

void clean_board(char * board)
{
    delete[] board;
}

void print_board(char * board, std::size_t x_dim, std::size_t y_dim)
{
    for(int i {0};i<y_dim;i++)
    {
        for(int j {0};j<x_dim;j++)
        {
            if(board[i*x_dim+j]&marked_mask())
            {
                std::cout<<'M';
            }
            else if(board[i*x_dim+j]&hidden_mask())
            {
                std::cout<<'*';
            }
            else
            {
                std::cout<<(board[i*x_dim+j]&value_mask());
            }
        }
        std::cout<<std::endl;
    }
}

void hide_board(char * board, std::size_t x_dim, std::size_t y_dim)
{
    for(int i {0};i<x_dim*y_dim;i++)
    {
        board[i]+=hidden_mask();
    }
}

int mark(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{
    if(!(board[y_loc*x_dim+x_loc]&hidden_mask()))
    {
        return 2;
    }
    else
    {
        board[y_loc*x_dim+x_loc]^=marked_mask();
        return 0;
    }

}





void compute_neighbours(char * board, std::size_t x_dim, std::size_t y_dim)
{

    for(int row{0};row<y_dim;row++)
    {
        for(int col{0};col<x_dim;col++)
        {
            if((board[row*x_dim+col]!=9))
            {
                for(int y{row-1};y<=row+1;y++)
                {
                    for(int x{col-1};x<=col+1;x++)
                    {
                        if((y>=0) && (x>=0))
                        {
                            if((y<y_dim) && (x<x_dim))
                            {
                                if(board[y*x_dim+x]==9)
                                {
                                    board[row*x_dim+col]++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool is_game_won(char * board, std::size_t x_dim, std::size_t y_dim)
{
    for(int col{0};col<y_dim;col++)
    {
        for(int row{0};row<x_dim;row++)
        {
            if((board[col*x_dim+row]&hidden_mask()) && ((board[col*x_dim+row]&value_mask())!=9))
            {    return false;}
        }
    }
    return true;
}

int reveal(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{
    if(board[y_loc*x_dim+x_loc]&marked_mask())
        return 1;
    if(!(board[y_loc*x_dim+x_loc]&hidden_mask()))
        return 2;
    if((board[y_loc*x_dim+x_loc]&value_mask())==9)
    {
        board[y_loc*x_dim+x_loc]-=hidden_mask();
        return 9;
    }
    if((board[y_loc*x_dim+x_loc]&value_mask())==0)
    {
        for(int col{(int)(y_loc-1)};col<=(int)(y_loc+1);col++)
        {
            for(int row{(int)(x_loc-1)};row<=(int)(x_loc+1);row++)
            {
                if((col>=0)&&(row>=0))
                {
                    if((row<x_dim)&&(col<y_dim))
                    {
                        if((board[col*x_dim+row]&hidden_mask())&&(!(board[col*x_dim+row]&marked_mask())))
                        {
                            board[col*x_dim+row]-=hidden_mask();
                        }
                    }
                }
            }
        }
        return 0;
    }
    else
    {
        board[y_loc*x_dim+x_loc]&=(~hidden_mask());
        return 0;
    }

}
