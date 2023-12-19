//
//  Score.cpp
//  Bunco
//
//  Created by Howard Stahl on 2/21/22.
//  Copyright © 2022 Howard Stahl. All rights reserved.
//

#include "Score.h"
#include <stdexcept>

namespace cs31
{

// setup a default score - all WRONG ANSWER's
Score::Score()
{
    for( int i = 0; i < REQUIREDLENGTH; i++ )
    {
        array[ i ] = ANSWER::WRONG;
    }
}

// TODO comparing the played move to the answer move,
//      build the ANSWER array of this Score
Score::Score( Move move, Move answer )
{
    for( int i = 0; i < REQUIREDLENGTH; i++ )
    {
        array[ i ] = ANSWER::WRONG;
    }
    for(int i = 0; i < REQUIREDLENGTH; i++){
        if(move.getPiece(i).getLetterAsString()==answer.getPiece(i).getLetterAsString()){
            array[i] = ANSWER::RIGHT;
            answer.setPiece(i, " ");
        }
    } //Scoring all matched up pieces as RIGHT.
    for(int i  = 0; i< REQUIREDLENGTH; i++){
        for(int j = 0; j < REQUIREDLENGTH; j++){
            if(array[i]!=ANSWER::RIGHT && move.getPiece(i).getLetterAsString()==answer.getPiece(j).getLetterAsString()){
                array[i] = ANSWER::MAYBE;
                answer.setPiece(j, " ");
            }
                //Any piece which wasn't matched as right but has a matching piece in a different spot is considered a MAYBE.
        }
        //Everything else is marked as wrong.
    }
}

// trivial getter but throw logic_error if the index is out of range
ANSWER Score::getAnswer( int i )
{
    if (i >= 0 && i < REQUIREDLENGTH)
        return( array[ i ] );
    else
        throw std::logic_error( "invalid i value" );
}

// stringify this Score
std::string Score::to_string() const
{
    std::string s = "";
    int mCount = 0;
    int rCount = 0;
    for (int i = 0; i < REQUIREDLENGTH; i++)
    {
        switch( array[i] )
        {
            case ANSWER::WRONG:
                // wrongs should not be printed at all
                s += "_";
                break;
            case ANSWER::RIGHT:
                rCount++;
                s += "R";
                break;
            case ANSWER::MAYBE:
                mCount++;
                s += "M";
                break;
        }
    }
    return( s );
}

// TODO is the ANSWER array all RIGHT ANSWER's?
bool Score::isExactMatch() const
{
    bool allCorr = true;
    for(int i = 0; i < REQUIREDLENGTH; i++){
        if(array[i]!=ANSWER::RIGHT){
            allCorr = false;
        }
    }//Returns true unless a single piece is not RIGHT.
    return allCorr;
}

}
