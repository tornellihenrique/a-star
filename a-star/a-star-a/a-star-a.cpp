//
//  a-star.cpp
//  a-star
//
//  Created by Henrique Tornelli on 01/06/22.
//

#include "a-star-a.hpp"

bool AStarA::isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool AStarA::isUnBlocked(int grid[][COL], int row, int col)
{
    if (grid[row][col] == 1)
        return true;
    else
        return false;
}

bool AStarA::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

double AStarA::calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double) sqrt((row - dest.first) * (row - dest.first)
                          + (col - dest.second) * (col - dest.second)));
}

void AStarA::tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nThe Path is ");
    
    int row = dest.first;
    int col = dest.second;
    
    stack<Pair> Path;
    
    while (!(cellDetails[row][col].parentI == row && cellDetails[row][col].parentJ == col)) {
        Path.push(make_pair(row, col));
        
        int tempRow = cellDetails[row][col].parentI;
        int tempCol = cellDetails[row][col].parentJ;
        
        row = tempRow;
        col = tempCol;
    }
    
    Path.push(make_pair(row, col));
    
    while (!Path.empty()) {
        Pair p = Path.top();
        
        Path.pop();
        
        printf("-> (%d,%d) ", p.first, p.second);
    }
    
    printf("\n");
    
    return;
}

void AStarA::search(int grid[][COL], Pair src, Pair dest)
{
    // Initial checks
    
    if (!isValid(src.first, src.second)) {
        printf("Source is invalid\n");
        
        return;
    }
    
    if (!isValid(dest.first, dest.second)) {
        printf("Destination is invalid\n");
        
        return;
    }
    
    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) {
        printf("Source or the destination is blocked\n");
        
        return;
    }
    
    if (isDestination(src.first, src.second, dest)) {
        printf("We are already at the destination\n");
        
        return;
    }
    
    // Create a closed list and initialise it to false which means that no cell has been included yet. This closed list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList)); // Setting everything to false
    
    // Declare a 2D array of structure to hold the details of that cell
    cell cellDetails[ROW][COL];
    
    int i, j;
    
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parentI = -1;
            cellDetails[i][j].parentJ = -1;
        }
    }
    
    // Initialising the parameters of the starting node
    i = src.first;
    j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parentI = i;
    cellDetails[i][j].parentJ = j;
    
    /*
     Create an open list having information as <f, <i, j>> where f = g + h, and i, j are the row and column index of that cell.
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair ofpair.
     */
    set<pPair> openList;
    
    // Put the starting cell on the open list and set its 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));
    
    // We set this boolean value as false as initially the destination is not reached.
    bool foundDest = false;
    
    while (!openList.empty()) {
        pPair p = *openList.begin();
        
        // Remove this vertex from the open list
        openList.erase(openList.begin());
        
        // Add this vertex from the open list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        
        /*
         Generating all the 8 successor of this cell
         
         N.W   N   N.E
         \   |   /
         \  |  /
         W----Cell----E
         / | \
         /   |  \
         S.W    S   S.E
         
         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West        (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)
         */
        
        // To store the 'g', 'h' and 'f' of the 8 sucessors
        double gNew, hNew, fNew;
        
        //----------- 1st Successor (North) ------------
        
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i - 1, j, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parentI = i;
                cellDetails[i - 1][j].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i - 1][j] && isUnBlocked(grid, i - 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                
                if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));
                    
                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parentI = i;
                    cellDetails[i - 1][j].parentJ = j;
                }
            }
        }
        
        //----------- 2nd Successor (South) ------------
        
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i + 1, j, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parentI = i;
                cellDetails[i + 1][j].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i + 1][j] && isUnBlocked(grid, i + 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parentI = i;
                    cellDetails[i + 1][j].parentJ = j;
                }
            }
        }
        
        //----------- 3rd Successor (East) ------------
        
        // Only process this cell if this is a valid one
        if (isValid(i, j + 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i, j + 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parentI = i;
                cellDetails[i][j + 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i][j + 1] && isUnBlocked(grid, i, j + 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j + 1)));
                    
                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parentI = i;
                    cellDetails[i][j + 1].parentJ = j;
                }
            }
        }
        
        //----------- 4th Successor (West) ------------
        
        // Only process this cell if this is a valid one
        if (isValid(i, j - 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i, j - 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parentI = i;
                cellDetails[i][j - 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i][j - 1] && isUnBlocked(grid, i, j - 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j - 1)));
                    
                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parentI = i;
                    cellDetails[i][j - 1].parentJ = j;
                }
            }
        }
        
        //----------- 5th Successor (North-East)
        //------------
        
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i - 1, j + 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parentI = i;
                cellDetails[i - 1][j + 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i - 1][j + 1] && isUnBlocked(grid, i - 1, j + 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == FLT_MAX || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));
                    
                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parentI = i;
                    cellDetails[i - 1][j + 1].parentJ = j;
                }
            }
        }
        
        //----------- 6th Successor (North-West)
        //------------
        
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i - 1, j - 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parentI = i;
                cellDetails[i - 1][j - 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i - 1][j - 1] && isUnBlocked(grid, i - 1, j - 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == FLT_MAX || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
                    
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parentI = i;
                    cellDetails[i - 1][j - 1].parentJ = j;
                }
            }
        }
        
        //----------- 7th Successor (South-East)
        //------------
        
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i + 1, j + 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parentI = i;
                cellDetails[i + 1][j + 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i + 1][j + 1] && isUnBlocked(grid, i + 1, j + 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == FLT_MAX || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j + 1)));
                    
                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parentI = i;
                    cellDetails[i + 1][j + 1].parentJ = j;
                }
            }
        }
        
        //----------- 8th Successor (South-West)
        //------------
        
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1)) {
            // If the destination cell is the same as the current successor
            if (isDestination(i + 1, j - 1, dest)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parentI = i;
                cellDetails[i + 1][j - 1].parentJ = j;
                
                printf("The destination cell is found\n");
                
                tracePath(cellDetails, dest);
                
                foundDest = true;
                
                return;
            }
            
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (!closedList[i + 1][j - 1] && isUnBlocked(grid, i + 1, j - 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;
                
                // If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == FLT_MAX || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j - 1)));
                    
                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parentI = i;
                    cellDetails[i + 1][j - 1].parentJ = j;
                }
            }
        }
    }
    
    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (!foundDest)
        printf("Failed to find the Destination Cell\n");
 
    return;
}
