import chess.pgn


def advance_moves(game):
    nmoves = len(list(game.mainline_moves()))
    board = game.board()
    i = 0
    for move in game.mainline_moves():
        board.push(move)
        i += 1
        if i > nmoves - 2:
            break
    return board


filename = "lichess_db_standard_rated_2013-01.pgn"

pgn = open(filename)

game = chess.pgn.read_game(pgn)

idx = 0
while game:
    board = advance_moves(game)
    with open(f"game_{idx+1:0>3}.tab", 'w') as fd:
        fd.write(str(board))
    with open(f"game_{idx+1:0>3}.pgn", 'w') as fd:
        fd.write(str(game))
    idx += 1
    if idx > 100000:
        break
    game = chess.pgn.read_game(pgn)
