package contest1

fun walkThrough(graph: Array<MutableSet<Int>>, node: Int, nodes: Array<Int>, currComp: Int) {
    nodes[node] = currComp
    graph[node].forEach { edge ->
        if (nodes[edge] == 0) {
            walkThrough(graph, edge, nodes, currComp)
        }
    }
}

fun main(args: Array<String>) {
    var input = readln().split(' ').map { it.toInt() }
    val n: Int = input[0]
    val m: Int = input[1]
    val nodes: Array<Int> = Array(n) { 0 }
    var componentsNumber = 0
    val graph: Array<MutableSet<Int>> = Array(n) { mutableSetOf() }
    for (i in 0..<m) {
        input = readln().split(' ').map { it.toInt() }
        graph[input[0] - 1].add(input[1] - 1)
        graph[input[1] - 1].add(input[0] - 1)
    }

    for (i in 0..<n) {
        if (nodes[i] != 0) continue

        componentsNumber++
        walkThrough(graph, i, nodes, componentsNumber)
    }

    println(componentsNumber)
    nodes.forEach { print(it); print(" ") }
}