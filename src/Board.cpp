#include "helper/Board.h"

// Constructor
Board::Board(){
    // 0. Set private member variables
    for(int i = 0; i < 2; i++){
        castle_short[i] = true;
        castle_long[i] = true;
    }

    // 1. Initialize the Tiles that are empty (rows 3 to 6)
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = Tile(i, j);
        }
    }

    // 2. Initialize the pawns
    for(int i = 0; i < 8; i++){
        board[1][i] = Tile("P", 0, 1, i);
        pieces[0].push_back(&board[1][i]);
        board[6][i] = Tile("P", 1, 6, i);
        pieces[1].push_back(&board[6][i]);
    }

    // 3. Initialize pieces from the first and last row
    // 3.1 Rooks, Knights and Bishops
    for(int i = 0; i < 3; i++){ // loop for pieces 0=rook, 1=knight, 2=bishop
        for(int j = 0; j < 2; j++){ // loop for players
            int playerRow = j * 7; 
            std::string piece = "R";
            if(i == 1)
                piece = "N";
            if(i == 2)
                piece = "B";

            board[playerRow][i] = Tile(piece, j, playerRow, i);
            pieces[j].push_back(&board[playerRow][i]);
            board[playerRow][7-i] = Tile(piece, j, playerRow, 7-i);
            pieces[j].push_back(&board[playerRow][7-i]);
        }
    }

    // 3.2 Kings and Queens
    for(int j = 0; j < 2; j++){
        int playerRow =  j*7;
        board[playerRow][3] = Tile("Q", j, playerRow, 3);
        pieces[j].push_back(&board[playerRow][3]);
        board[playerRow][4] = Tile("K", j, playerRow, 4);
        pieces[j].push_back(&board[playerRow][4]);
    }
}

// Copy Constructor
Board::Board(std::vector<Tile*> copyPieces[2], bool cshort[2], bool clong[2]){
    // 0. Copy member variables
    for(int i = 0; i < 2; i++){
        castle_short[i] = cshort[i];
        castle_long[i] = clong[i];
    }

    // 1. Initialize all Tiles as empty
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            board[i][j] = Tile(i, j);

    // 2. Assign Tiles with pieces
    for(int i = 0; i < 2; i++)
        for(auto p : copyPieces[i]){
            int row = p->GetRow(), col = p->GetCol();
            board[row][col] = Tile(p->GetPiece(), p->GetPlayer(), row, col);
            pieces[i].push_back(&board[row][col]);
        }
}

void Board::PieceMoves(std::unordered_map<std::string, std::vector<Move>>& moves, Tile* aTile, bool turn){
    // checks all possible moves from a piece, pins and checks unincluded
    //auto [row, col] = PtoC(position);
    //Tile& aTile = board[row][col];
    int row = aTile->GetRow(), col = aTile->GetCol();
    std::string notation = "";

    if (aTile->GetPlayer() != turn)
        return;

    if(aTile->GetPiece() == "P") {
        notation = ColToLetter(col);
        int forward = turn? -1 : 1;
        if(board[row + forward][col + 1].GetPlayer() == (!turn) && col + 1 < 8){
            std::string extra = "x" + CtoP(row + forward, col + 1);
            moves[notation + extra].push_back(Move(notation + extra, aTile, &board[row+forward][col+1]));
        }
        if(board[row + forward][col - 1].GetPlayer() == (!turn) && col - 1 >= 0){
            std::string extra = "x" + CtoP(row + forward, col - 1);
            moves[notation + extra].push_back(Move(notation + extra, aTile, &board[row+forward][col-1]));
        }
        if(board[row + forward][col].GetPlayer() != -1)
            return; 
        moves[CtoP(row + forward, col)].push_back(Move(CtoP(row + forward, col), aTile, &board[row+forward][col]));
        if(row == (turn ? 6 : 1))
            if(board[row + 2*forward][col].GetPlayer() == -1)
                moves[CtoP(row + 2*forward, col)].push_back(Move(CtoP(row + 2*forward, col), aTile, &board[row+2*forward][col]));
        // promotion missing
        // en passant missing
    }
    if(aTile->GetPiece() == "R") {
        bool advance[] = {true, true, true, true};
        for(int n = 1; n < 8; n++){
            bool conditions[4] = {row + n < 8, row - n >= 0, col + n < 8, col - n >= 0};
            int rows[4] = {row + n, row - n, row, row};
            int cols[4] = {col, col, col + n, col - n};
            for(int i = 0; i < 4; i++){
                if(!advance[i])
                    continue;
                if (!conditions[i]){
                    advance[i] = false;
                    continue;
                }
                Tile* currentTile = &board[rows[i]][cols[i]];
                if(currentTile->GetPlayer() == turn){
                    advance[i] = false;
                    continue;
                }
                notation = "R" + CtoP(rows[i], cols[i]);
                if(currentTile->GetPlayer() == (!turn)){
                    notation = "Rx" + CtoP(rows[i], cols[i]);   
                    advance[i] = false;
                }
                moves[notation].push_back(Move(notation, aTile, currentTile));
            }
        }
    }
    if(aTile->GetPiece() == "B") {
        bool advance[] = {true, true, true, true};
        for(int n = 1; n < 8; n++){
            bool conditions[4] = {row+n<8 && col+n<8, row+n<8 && col-n>=0, row-n>=0 && col+n<8, row-n>=0 && col-n>=0};
            int rows[4] = {row + n, row + n, row - n, row - n};
            int cols[4] = {col + n, col - n, col + n, col - n};
            for(int i = 0; i < 4; i++){
                if(!advance[i])
                    continue;
                if(!conditions[i]){
                    advance[i] = false;
                    continue;
                }
                Tile* currentTile = &board[rows[i]][cols[i]];
                if(currentTile->GetPlayer() == turn){
                    advance[i] = false;
                    continue;
                }
                notation = "B" + CtoP(rows[i], cols[i]);
                if(currentTile->GetPlayer() == (!turn)){
                    notation = "Bx" + CtoP(rows[i], cols[i]);
                    advance[i] = false;
                }
                moves[notation].push_back(Move(notation, aTile, currentTile));
            }
        }
    }
    if(aTile->GetPiece() == "N") {
        for(int vertical = 1; vertical < 3; vertical++){
            int horizontal = vertical == 1? 2 : 1;
            int dir[2] = {1, -1};
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 2; j++){
                    int jumpV = row + vertical*dir[i];
                    int jumpH = col + horizontal*dir[j];
                    if(jumpV >= 8 || jumpV < 0 || jumpH >= 8 || jumpH < 0)
                        continue;
                    Tile* currentTile = &board[jumpV][jumpH];
                    if(currentTile->GetPlayer() == turn)
                        continue;
                    notation = "N" + CtoP(jumpV, jumpH);
                    if(currentTile->GetPlayer() == (!turn))
                        notation = "Nx" + CtoP(jumpV, jumpH);
                    moves[notation].push_back(Move(notation, aTile, currentTile));
                }
            }            
        }
    }
    if(aTile->GetPiece() == "Q") {
        bool advance[2][4] = {{true, true, true, true}, // for rook moves
                                {true, true, true, true}};// for bishop moves
        for(int n = 1; n < 8; n++){
            bool conditions[2][4] = 
                {{row + n < 8, row - n >= 0, col + n < 8, col - n >= 0},
                    {row+n<8 && col+n<8, row+n<8 && col-n>=0, row-n>=0 && col+n<8, row-n>=0 && col-n>=0}};
            int rows[2][4] = {{row + n, row - n, row, row},
                                {row + n, row + n, row - n, row - n}};
            int cols[2][4] = {{col, col, col + n, col - n},
                                {col + n, col - n, col + n, col - n}};
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 2; j++){
                    if(!advance[j][i])
                        continue;
                    if(!conditions[j][i]){
                        advance[j][i] = false;
                        continue;
                    }

                    Tile* currentTile = &board[rows[j][i]][cols[j][i]];
                    if(currentTile->GetPlayer() == turn){
                        advance[j][i] = false;
                        continue;
                    }
                    notation = "Q" + CtoP(rows[j][i], cols[j][i]);
                    if(currentTile->GetPlayer() == (!turn)){
                        notation = "Qx" + CtoP(rows[j][i], cols[j][i]);
                        advance[j][i] = false;
                    }
                    moves[notation].push_back(Move(notation, aTile, currentTile));
                }
            }
        }
    }
    if(aTile->GetPiece() == "K") {
        int n = 1;
        bool conditions[2][4] = 
            {{row + n < 8, row - n >= 0, col + n < 8, col - n >= 0},
                {row+n<8 && col+n<8, row+n<8 && col-n>=0, row-n>=0 && col+n<8, row-n>=0 && col-n>=0}};
        int rows[2][4] = {{row + n, row - n, row, row},
                            {row + n, row + n, row - n, row - n}};
        int cols[2][4] = {{col, col, col + n, col - n},
                            {col + n, col - n, col + n, col - n}};
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 2; j++){
                if(!conditions[j][i]){
                    continue;
                }

                Tile* currentTile = &board[rows[j][i]][cols[j][i]];
                if(currentTile->GetPlayer() == turn)
                    continue;
                notation = "K" + CtoP(rows[j][i], cols[j][i]);
                if(currentTile->GetPlayer() == (!turn))
                    notation = "Kx" + CtoP(rows[j][i], cols[j][i]);
                moves[notation].push_back(Move(notation, aTile, currentTile));
            }
        }
    }
    // castling missing
}

std::unordered_map<std::string, std::vector<Move>> Board::PossibleMoves(bool turn){
    std::unordered_map<std::string, std::vector<Move>> moves;
    for(auto piece : pieces[turn])  
        PieceMoves(moves, piece, turn);
    return moves;
}

void Board::PrintBoard(){
    std::cout << std::endl;
    for(int i = 7; i >= 0; i--){
        std::cout << i+1;
        for(int j = 0; j <= 7; j++){
            std::string tile_print = "";
            if((i+j) % 2 == 1) {
                if(board[i][j].GetPlayer() == 0)
                    tile_print = "\033[37;47m " + board[i][j].GetPiece() + " \33[0m";
                else if(board[i][j].GetPlayer() == 1)
                    tile_print = "\033[30;47m " + board[i][j].GetPiece() + " \33[0m";
                else
                    tile_print = "\033[33;47m   \33[0m";
            }
            else { // black tiles
                if(board[i][j].GetPlayer() == 0)
                    tile_print = "\033[37;42m " + board[i][j].GetPiece() + " \33[0m";
                else if(board[i][j].GetPlayer() == 1)
                    tile_print = "\033[30;42m " + board[i][j].GetPiece() + " \33[0m";
                else
                    tile_print = "\033[30;42m   \33[0m";
            }
            std::cout << "\033[1m" << tile_print;

                
        }
        std::cout << "\n";
    }
    std::cout << "  a  b  c  d  e  f  g  h " << std::endl;
    std::cout << std::endl;
}

void Board::MovePiece(std::string start, std::string end){
    // for this function to happen, the move MUST be legal (checks before calling the function)
    std::pair<int, int> a = PtoC(start);
    std::pair<int, int> b = PtoC(end);

    // pass all the information from a to b
    board[a.first][a.second].MovePiece(&board[b.first][b.second]);
}

void Board::MovePiece(Move m, bool turn){
    if(m.fromTile->GetPiece() == "K"){
        DisableCastling(turn);
    }
    if(m.fromTile->GetPiece() == "R"){
        if(m.fromTile->GetCol() == 7)
            castle_short[turn] = false;
        if(m.fromTile->GetCol() == 0)
            castle_long[turn] = false;
    }
    for(auto& p : pieces[turn])
        if(p == m.fromTile)
            p = m.toTile;
    if(m.toTile->GetPlayer() == (!turn))
        for(int i = 0; i < pieces[!turn].size(); i++)
            if(pieces[!turn].at(i) == m.toTile){
                pieces[!turn].erase(pieces[!turn].begin() + i);
                break;
            }
                
    m.fromTile->MovePiece(m.toTile);
    log.push_back(m);
}

std::unordered_map<std::string, std::vector<Move>> Board::LegalMoves(bool turn){
    std::unordered_map<std::string, std::vector<Move>> moves, possibles = PossibleMoves(turn);
    for(auto m : possibles)
        for(int i = 0; i < possibles[m.first].size(); i++){
            Board b(pieces, castle_short, castle_long);
            std::unordered_map<std::string, std::vector<Move>> copyMoves = b.PossibleMoves(turn);
            b.MovePiece(copyMoves[m.first].at(i), turn);
                if(b.Check(!turn) == false)
                    moves[m.first].push_back(possibles[m.first].at(i));
        }
    if(castle_short[turn] && Castle(turn, 5, 6)){ 
        moves["0-0"].push_back(Move("0-0", &board[7*turn][4], &board[7*turn][6]));
        moves["0-0"].push_back(Move("0-0", &board[7*turn][7], &board[7*turn][5]));
    }
    if(castle_long[turn] && Castle(turn, 2, 3)){ 
        moves["0-0-0"].push_back(Move("0-0-0", &board[7*turn][4], &board[7*turn][2]));
        moves["0-0-0"].push_back(Move("0-0-0", &board[7*turn][0], &board[7*turn][3]));
    }
    return moves;
}

bool Board::Check(bool turn){
    for(auto n : PossibleMoves(turn))
        for(auto m : n.second)
            if(m.toTile->GetPiece() == "K")
                return true;
    return false;
}

bool Board::Checkmate(bool turn){
    if(Check(turn) && LegalMoves(!turn).size() == 0)
        return true;
    return false;
}

bool Board::Stalemate(bool turn){
    if(!Check(turn) && LegalMoves(!turn).size() == 0)
        return true;
    return false;
}

bool Board::Castle(bool turn, int c1, int c2){
    int row = 7*turn;
    if(board[row][c1].GetPlayer() != -1 || board[row][c2].GetPlayer() != -1 || Check(!turn))
        return false;
    for(auto n : PossibleMoves(!turn))
        for(auto m : n.second){
            if(m.toTile->GetRow() == row && m.toTile->GetCol() == c1)
                return false;
            if(m.toTile->GetRow() == row && m.toTile->GetCol() == c2)
                return false;
        }
    return true;   
}

void Board::DisableCastling(bool turn){
    castle_short[turn] = false;
    castle_long[turn] = false;
}

// coordinates <> position funcitons
std::string CtoP(int row, int column){
    return std::string(1, column + 'a') + std::string(1, row + '1');
}
std::pair<int, int> PtoC(std::string position){
    return std::pair<int, int> (position[1] - '1', position[0] - 'a');
}
char ColToLetter(int col){
    return col + 'a';
}