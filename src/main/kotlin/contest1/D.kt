package contest1

import java.util.*
import kotlin.math.absoluteValue

data class Wall(val startX: Int, val startY: Int, val endX: Int, val endY: Int, val t: Int) {
    fun isWallAt(x: Int, y: Int, time: Int): Boolean {
        if (t == 0) {
            return x == startX && y == startY
        }

        val period = 2 * ((endX - startX).absoluteValue + (endY - startY).absoluteValue) * t
        val phase = (time % period) / t
        val deltaX = (endX - startX)
        val deltaY = (endY - startY)
        val steps = (deltaX.absoluteValue + deltaY.absoluteValue)
        val fullPhase = 2 * steps

        return when {
            phase < steps -> {
                x == startX + (phase * deltaX / steps) && y == startY + (phase * deltaY / steps)
            }
            phase < fullPhase -> {
                x == endX - ((phase - steps) * deltaX / steps) && y == endY - ((phase - steps) * deltaY / steps)
            }
            else -> false
        }
    }
}

fun main() {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val m = scanner.nextInt()
    val k = scanner.nextInt()

    val walls = ArrayList<Wall>()
    for (i in 0..<k) {
        val sx = scanner.nextInt() - 1
        val sy = scanner.nextInt() - 1
        val fx = scanner.nextInt() - 1
        val fy = scanner.nextInt() - 1
        val t = scanner.nextInt()
        walls.add(Wall(sx, sy, fx, fy, t))
    }

    val directions = arrayOf(Pair(0, 1), Pair(1, 0), Pair(0, -1), Pair(-1, 0))
    val directionChars = arrayOf('R', 'D', 'L', 'U')

    val queue: Queue<Triple<Int, Int, Int>> = LinkedList()
    val visited = Array(n) { Array(m) { BooleanArray(n * m * 4) } }
    queue.add(Triple(0, 0, 0))
    visited[0][0][0] = true

    val parent = mutableMapOf<Triple<Int, Int, Int>, Pair<Triple<Int, Int, Int>, Char>>()

    while (queue.isNotEmpty()) {
        val (x, y, time) = queue.poll()

        if (x == n - 1 && y == m - 1) {
            val path = StringBuilder()
            var current = Triple(x, y, time)
            while (current != Triple(0, 0, 0)) {
                val (prev, move) = parent[current]!!
                path.append(move)
                current = prev
            }
            println(path.reverse().toString())
            return
        }

        for (i in directions.indices) {
            val nx = x + directions[i].first
            val ny = y + directions[i].second
            val ntime = time + 1
            if (nx in 0..<n && ny in 0..<m && !visited[nx][ny][ntime % (n * m * 4)]) {
                if (walls.none { it.isWallAt(nx, ny, ntime) }) {
                    visited[nx][ny][ntime % (n * m * 4)] = true
                    queue.add(Triple(nx, ny, ntime))
                    parent[Triple(nx, ny, ntime)] = Triple(x, y, time) to directionChars[i]
                }
            }
        }
    }

    println("N")
}
