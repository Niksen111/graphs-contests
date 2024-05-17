package contest1

import kotlin.math.max
import kotlin.math.min

fun main(args: Array<String>) {
    var graph = emptyArray<MutableSet<Int>>()
    var graphReduced: Array<MutableSet<Int>> = emptyArray()
    var cycles: Long = 0L
    var input = readln().split(' ').map { it.toInt() }
    val n: Int = input[0]
    val m: Int = input[1]
    graph = Array(n) { mutableSetOf() }
    graphReduced = Array(n) { mutableSetOf() }
    for (i in 0..<m) {
        input = readln().split(' ').map { it.toInt() }
        val a = input[0] - 1
        val b = input[1] - 1

        graph[a].add(b)
        graph[b].add(a)
        graphReduced[min(a, b)].add(max(a, b))
    }

    for (a in 0..<n) {
        graphReduced[a].forEach { b ->
            graphReduced[b].forEach { c ->
                if (graph[c].contains(a)) cycles++
            }
        }
    }

    println(cycles)
}