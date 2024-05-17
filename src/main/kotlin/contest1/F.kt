package contest1

val letterToNumber = mapOf(
    'a' to 0,
    'b' to 1,
    'c' to 2,
    'd' to 3,
    'e' to 4,
    'f' to 5,
    'g' to 6,
    'h' to 7
)
val numberToLetter = mapOf(
    0 to 'a',
    1 to 'b',
    2 to 'c',
    3 to 'd',
    4 to 'e',
    5 to 'f',
    6 to 'g',
    7 to 'h'
)

val moves = arrayOf(
    Pair(1, 2),
    Pair(1, -2),
    Pair(-1, 2),
    Pair(-1, -2),
    Pair(2, 1),
    Pair(2, -1),
    Pair(-2, 1),
    Pair(-2, -1),
)

val trajectories = Array<Array<List<Pair<Int, Int>>>>(8) { Array(8) { listOf() } }

fun inBoard(square: Pair<Int, Int>): Boolean {
    return square.first in 0..7 && square.second in 0..7
}

fun makeMove(square: Pair<Int, Int>, move: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(square.first + move.first, square.second + move.second)
}

fun colorMoves(board: Array<Array<Int>>, square: Pair<Int, Int>, number: Int): Set<Pair<Int, Int>> {
    val madeMoves = mutableSetOf<Pair<Int, Int>>()
    moves.forEach { move ->
        val newSquare = makeMove(square, move)
        if (inBoard(newSquare) && board[newSquare.first][newSquare.second] == 0) {
            board[newSquare.first][newSquare.second] = number
            madeMoves.add(newSquare)
            trajectories[newSquare.first][newSquare.second] = trajectories[square.first][square.second].plus(newSquare)
        }
    }

    return madeMoves
}

fun printSquare(square: Pair<Int, Int>) {
    println(numberToLetter[square.first].toString() + (square.second + 1))
}

fun colorCorner(board: Array<Array<Int>>, square: Pair<Int, Int>) {
    moves.forEach { move ->
        val newSquare = makeMove(square, move)
        if (inBoard(newSquare)) {
            board[square.first][square.second] = board[newSquare.first][newSquare.second] + 1
            trajectories[square.first][square.second] = trajectories[newSquare.first][newSquare.second].plus(square)
        }
    }
}

fun main(args: Array<String>) {
    val start = readln()
    val end = readln()
    val a = Pair(letterToNumber[start[0]]!!, start[1].toString().toInt() - 1)
    val b = Pair(letterToNumber[end[0]]!!, end[1].toString().toInt() - 1)
    val board = Array(8) { Array(8) { 0 } }
    board[a.first][a.second] = -1
    var colored = setOf(a)
    for (i in 1..5) {
        val newColored = mutableSetOf<Pair<Int, Int>>()
        colored.forEach { newColored.addAll(colorMoves(board, it, i)) }
        colored = newColored
    }

    if (board[0][0] == 0) colorCorner(board, Pair(0, 0))
    if (board[0][7] == 0) colorCorner(board, Pair(0, 7))
    if (board[7][0] == 0) colorCorner(board, Pair(7, 0))
    if (board[7][7] == 0) colorCorner(board, Pair(7, 7))


    println(start)
    trajectories[b.first][b.second].forEach {
        printSquare(it)
    }
}