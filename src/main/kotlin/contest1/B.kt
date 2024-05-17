package contest1

var found: Boolean = false
var nodes: Array<Int> = emptyArray()
var graph = emptyArray<MutableSet<Int>>()

val stack = ArrayDeque<Int>()

fun dfs(node: Int) {
    if (found) return
    nodes[node] = 1
    stack.add(node)

    graph[node].forEach { to ->
        if (nodes[to] == 1) {
            stack.add(to)
            found = true
            return
        } else dfs(to)
        if (found) return
    }

    nodes[node] = 2
    stack.removeLast()
}

fun main(args: Array<String>) {
    var input = readln().split(' ').map { it.toInt() }
    val n: Int = input[0]
    val m: Int = input[1]
    nodes = Array(n) { 0 }
    graph = Array(n) { mutableSetOf() }
    for (i in 0..<m) {
        input = readln().split(' ').map { it.toInt() }
        graph[input[0] - 1].add(input[1] - 1)
    }

    for (i in 0..<n) {
        if (nodes[i] != 0) continue

        dfs(i)
        if (found) break
    }

    if (!found) {
        println("NO")
    } else {
        println("YES")
        val result = mutableListOf<Int>()
        result.add(stack.removeLast())
        var kek = stack.removeLast()
        do {
            result.add(kek)
            kek = stack.removeLast()
        } while (kek != result[0])

        result.reverse()
        result.forEach { print(it + 1); print(" ") }
    }
}