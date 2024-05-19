package contest1

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val m = scanner.nextInt()
    val graph = Array(n + 1) { mutableListOf<Int>() }

    repeat(n - 1) {
        val u = scanner.nextInt()
        val v = scanner.nextInt()
        graph[u].add(v)
        graph[v].add(u)
    }

    fun bfs(start: Int): Pair<Int, Int> {
        val dist = IntArray(n + 1) { -1 }
        val queue: Queue<Int> = LinkedList()
        queue.add(start)
        dist[start] = 0

        var farthestNode = start
        while (queue.isNotEmpty()) {
            val node = queue.poll()
            for (neighbor in graph[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1
                    queue.add(neighbor)
                    if (dist[neighbor] > dist[farthestNode]) {
                        farthestNode = neighbor
                    }
                }
            }
        }
        return Pair(farthestNode, dist[farthestNode])
    }

    val firstBFS = bfs(1)
    val secondBFS = bfs(firstBFS.first)
    val diameter = secondBFS.second

    if (diameter >= m) {
        println(m + 1)
    } else {
        println(minOf(n, diameter + 1 + (m - diameter) / 2))
    }
}