import java.util.Scanner

fun floyd(d: Array<IntArray>): Array<IntArray> {
    val vCnt = d.size
    val next = Array(vCnt) { IntArray(vCnt) { it } }

    for (k in 0..<vCnt) {
        for (i in 0..<vCnt) {
            for (j in 0..<vCnt) {
                if (d[i][k] > -inf && d[k][j] > -inf && d[i][k] + d[k][j] > d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j]
                    next[i][j] = next[i][k]
                }
            }
        }
    }
    return next
}

fun findCycles(d: Array<IntArray>) {
    val vCnt = d.size
    for (i in 0..<vCnt) {
        for (j in 0..<vCnt) {
            for (t in 0..<vCnt) {
                if (d[i][t] > -inf && d[t][t] > 0 && d[t][j] > -inf) {
                    d[i][j] = inf
                }
            }
        }
    }
}

fun getPath(u: Int, v: Int, d: Array<IntArray>, next: Array<IntArray>): List<Int> {
    if (d[u][v] == -inf) {
        return emptyList()
    } else if (d[u][v] == inf) {
        return listOf(0)
    }

    val path = mutableListOf<Int>()
    var c = u
    while (c != v) {
        path.add(c)
        c = next[c][v]
    }
    path.add(v)
    return path
}

const val inf = Int.MAX_VALUE

fun main() {
    val scanner = Scanner(System.`in`)

    val (vCnt, eCnt, townSequenceLen) = scanner.nextLine().split(" ").map { it.toInt() }

    val distances = Array(vCnt) { IntArray(vCnt) }
    val flightNumbers = Array(vCnt) { IntArray(vCnt) }

    repeat(eCnt) {
        val (v, u, w) = scanner.nextLine().split(" ").map { it.toInt() }
        distances[v - 1][u - 1] = w
        flightNumbers[v - 1][u - 1] = it + 1
    }

    for (i in 0..<vCnt) {
        for (j in 0..<vCnt) {
            if (i != j && distances[i][j] == 0) {
                distances[i][j] = -inf
            }
        }
    }

    val townSequence = scanner.nextLine().split(" ").map { it.toInt() - 1 }

    val next = floyd(distances)
    findCycles(distances)

    val flightSequence = mutableListOf<Int>()
    var infinitePath = false

    for (i in 0..<townSequenceLen - 1) {
        val path = getPath(townSequence[i], townSequence[i + 1], distances, next)
        if (path.isEmpty()) {
            println("no path")
            infinitePath = true
            break
        } else if (path.size == 1) {
            println("infinitely kind")
            infinitePath = true
            break
        }
        for (k in 0..<path.size - 1) {
            flightSequence.add(flightNumbers[path[k]][path[k + 1]])
        }
    }

    if (!infinitePath) {
        println(flightSequence.size)
        println(flightSequence.joinToString(" "))
    }
}