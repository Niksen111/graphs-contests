package contest2

import java.util.*

data class Edge(val u: Int, val v: Int, val weight: Int)

fun find(parent: IntArray, x: Int): Int {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x])
    }
    return parent[x]
}

fun union(parent: IntArray, rank: IntArray, x: Int, y: Int) {
    val rootX = find(parent, x)
    val rootY = find(parent, y)

    if (rootX != rootY) {
        when {
            rank[rootX] < rank[rootY] -> parent[rootX] = rootY
            rank[rootX] > rank[rootY] -> parent[rootY] = rootX
            else -> {
                parent[rootY] = rootX
                rank[rootX]++
            }
        }
    }
}

fun main() {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val m = scanner.nextInt()
    val edges = mutableListOf<Edge>()

    for (i in 0..<m) {
        val u = scanner.nextInt()
        val v = scanner.nextInt()
        val weight = scanner.nextInt()
        edges.add(Edge(u, v, weight))
    }

    edges.sortBy { it.weight }

    val parent = IntArray(n + 1) { it }
    val rank = IntArray(n + 1) { 0 }

    var mstWeight = 0
    var edgesUsed = 0

    for (edge in edges) {
        if (find(parent, edge.u) != find(parent, edge.v)) {
            union(parent, rank, edge.u, edge.v)
            mstWeight += edge.weight
            edgesUsed++
            if (edgesUsed == n - 1) break
        }
    }

    println(mstWeight)
}
