package contest3

import kotlin.math.*

data class Exchanger(val from: Int, val to: Int, val rate: Double, val comm: Double)

fun canIncreaseAmount(currenciesCnt: Int, startCurrency: Int, startAmount: Double, exchangers: List<Exchanger>): Boolean {
    val d = DoubleArray(currenciesCnt) { Double.NEGATIVE_INFINITY }
    d[startCurrency] = startAmount

    for (i in 0..<currenciesCnt - 1) {
        for (e in exchangers) {
            if (d[e.from] > Double.NEGATIVE_INFINITY && (d[e.from] - e.comm) * e.rate > max(0.0, d[e.to])) {
                d[e.to] = (d[e.from] - e.comm) * e.rate
            }
        }
    }

    val used = BooleanArray(currenciesCnt)
    for (e in exchangers) {
        if (d[e.from] > Double.NEGATIVE_INFINITY && (d[e.from] - e.comm) * e.rate > max(0.0, d[e.to])) {
            findPath(e.to, used, exchangers)
            return used[startCurrency]
        }
    }
    return false
}

fun findPath(v: Int, used: BooleanArray, edges: List<Exchanger>) {
    used[v] = true
    for (edge in edges) {
        if (edge.from == v && !used[edge.to]) {
            findPath(edge.to, used, edges)
        }
    }
}

fun main() {
    val reader = System.`in`.bufferedReader()

    val firstLine = reader.readLine().trim().split(" ")
    val currenciesCnt = firstLine[0].toInt()
    val exchangersCnt = firstLine[1].toInt()
    val startCurrency = firstLine[2].toInt()
    val startAmount = firstLine[3].toDouble()

    val exchangers = mutableListOf<Exchanger>()
    for (i in 0..<exchangersCnt) {
        val line = reader.readLine().trim().split(" ")
        val a = line[0].toInt()
        val b = line[1].toInt()
        val rab = line[2].toDouble()
        val cab = line[3].toDouble()
        val rba = line[4].toDouble()
        val cba = line[5].toDouble()
        exchangers.add(Exchanger(a - 1, b - 1, rab, cab))
        exchangers.add(Exchanger(b - 1, a - 1, rba, cba))
    }

    if (canIncreaseAmount(currenciesCnt, startCurrency - 1, startAmount, exchangers)) {
        println("YES")
    } else {
        println("NO")
    }
}