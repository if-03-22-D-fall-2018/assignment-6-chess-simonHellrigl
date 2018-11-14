/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.c
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
 */  #include <stdlib.h>
  #include "general.h"
  #include "chess.h"

  void init_chess_board(ChessBoard chess_board){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        chess_board[i][j].is_occupied = false;
      }
    }
  }


   void setup_chess_board(ChessBoard chess_board)
   {
     File file;
     init_chess_board(chess_board);
     for (file = 'a'; file <= 'h'; file++) {
       add_piece(chess_board, file, 2, {White,Pawn});
  		  add_piece(chess_board, file, 7, {Black, Pawn});
     }

     //This is the side of the first Player (White)
     add_piece(chess_board , 'a', 1, {White, Rook});
     add_piece(chess_board , 'h', 1, {White, Rook});
     add_piece(chess_board , 'b', 1, {White, Knight});
     add_piece(chess_board , 'g', 1, {White, Knight});
     add_piece(chess_board , 'c', 1, {White, Bishop});
     add_piece(chess_board , 'f', 1, {White, Bishop});
     add_piece(chess_board , 'e', 1, {White, King});
     add_piece(chess_board , 'd', 1, {White, Queen});

     //This is Player2 (Black)
     add_piece(chess_board , 'a', 8, {Black, Rook});
     add_piece(chess_board , 'h', 8, {Black, Rook});
     add_piece(chess_board , 'b', 8, {Black, Knight});
     add_piece(chess_board , 'g', 8, {Black, Knight});
     add_piece(chess_board , 'c', 8, {Black, Bishop});
     add_piece(chess_board , 'f', 8, {Black, Bishop});
     add_piece(chess_board , 'e', 8, {Black, King});
     add_piece(chess_board , 'd', 8, {Black, Queen});

   }

   bool is_square_occupied(ChessBoard chess_board, File file, Rank rank)
   {
     int int_file = file - 97;
     if (chess_board[rank-1][int_file].is_occupied)
     {
       return true;
     }
     return false;
   }

   struct ChessSquare* get_square (ChessBoard chess_board, File file, Rank rank)
   {
     if((file > 'h' || file < 'a') || (rank > 8 || rank < 1))
     {
       return 0;
     }
     return (&chess_board[rank-1][file-97]);
   }

   bool add_piece(ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
   {
     int int_file = file - 97;
     if((file > 'h' || file < 'a') || (rank > 8 || rank < 1) || chess_board[rank-1][int_file].is_occupied)
     {
       return false;
     }
     else
     {
       chess_board[rank-1][int_file].is_occupied = true;
       chess_board[rank-1][int_file].piece = piece;
       return true;
     }
   }

   struct ChessPiece get_piece(ChessBoard chess_board, File file, Rank rank)
   {
     int int_file = file - 97;
     if(((file > 'h' || file < 'a') || (rank > 8 || rank < 1)) || chess_board[rank-1][int_file].is_occupied == false)
     {
       chess_board[rank-1][int_file].piece.type = NoPiece;
       return chess_board[rank-1][int_file].piece;
     }
     else
     {
       return chess_board[rank-1][file-97].piece;
     }
   }

   bool remove_piece(ChessBoard chess_board, File file, Rank rank)
   {
     int int_file = file - 97;
     if(((file > 'h' || file < 'a') || (rank > 8 || rank < 1)) || chess_board[rank-1][int_file].is_occupied == false)
     {
       return false;
     }
     else
     {
       chess_board[rank-1][int_file].is_occupied = false;
       chess_board[rank-1][int_file].piece.type = NoPiece;
       return true;
     }
   }

   bool is_piece(struct ChessPiece pc, enum Color color, enum PieceType type)
   {
     if (pc.color == color && pc.type == type) {
       return true;
     }
     return false;
   }


    //this 4 functions dont work jet the are just declared for the unitests;
    bool squares_share_knights_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
    {
      return false;
    }
    bool squares_share_pawns_move(enum Color color, enum Move move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
    {
      return false;
    }
    bool squares_share_queens_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
    {
      return false;
    }
    bool squares_share_kings_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
    {
      return false;
    }


    //  Prototyp für function welche ab hier verwendet wird;
    bool is_not_part_of_field(File file1, Rank rank1, File file2, Rank rank2);

    bool squares_share_file(File file1, Rank rank1, File file2, Rank rank2)
    {
      if(is_not_part_of_field(file1, rank1, file2, rank2))
      {
        return false;
      }
      else if (file1 == file2)
      {
      return true;
      }
      else
      {
        return false;
      }
    }

    bool squares_share_rank(File file1, Rank rank1, File file2, Rank rank2)
    {
      if(is_not_part_of_field(file1, rank1, file2, rank2))
      {
        return false;
      }
      else if (rank1 == rank2)
      {
      return true;
      }
      else
      {
        return false;
      }

    }


    bool squares_share_diagonal(File file1, Rank rank1, File file2, Rank rank2)
    {
      if(is_not_part_of_field(file1, rank1, file2, rank2))
      {
        return false;
      }
      else if (abs(file1 - file2) == abs(rank1 - rank2) || abs(file2 - file1) == abs(rank2 - rank1) || abs(file2 - file1) == abs(rank1 - rank2))
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    //this function checks if the coordinates of file1,rank1,file2,rank2 are on the ChessBoard
    bool is_not_part_of_field(File file1, Rank rank1, File file2, Rank rank2)
    {
      return (file1 > 'h' || file1 < 'a') || (file2 > 'h' || file2 < 'a') || (rank1 > 8 || rank1 < 1) || (rank2 > 8 || rank2 < 1);
    }
