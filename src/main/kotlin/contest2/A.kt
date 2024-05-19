package contest2

import java.util.Scanner

class DSU(n: Int) {
    private val parent = IntArray(n + 1) { it }
    private val rank = IntArray(n + 1) { 1 }

    fun find(x: Int): Int {
        if (parent[x] != x) {
            parent[x] = find(parent[x])
        }
        return parent[x]
    }

    fun union(u: Int, v: Int) {
        val rootU = find(u)
        val rootV = find(v)
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU
            } else {
                parent[rootV] = rootU
                rank[rootU] += 1
            }
        }
    }
}

fun main() {
    val scanner = Scanner(System.`in`)
    val n = scanner.nextInt()
    val m = scanner.nextInt()
    val dsu = DSU(n)

    repeat(m) {
        val queryType = scanner.next()
        val u = scanner.nextInt()
        val v = scanner.nextInt()
        when (queryType) {
            "union" -> dsu.union(u, v)
            "get" -> {
                val result = if (dsu.find(u) == dsu.find(v)) "YES" else "NO"
                println(result)
            }
        }
    }
}
