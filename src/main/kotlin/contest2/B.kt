import java.util.Scanner

class Groups(val p: IntArray, val xp: IntArray) {
    private fun find(n: Int): Pair<Int, Int> {
        if (p[n] == n) {
            return n to xp[n]
        }
        val (clanParent, clanXp) = find(p[n])
        p[n] = clanParent
        xp[n] += clanXp - xp[p[n]]
        return p[n] to xp[n] + xp[p[n]]
    }

    fun join(n: Int, m: Int) {
        var (pN, _) = find(n)
        var (pM, _) = find(m)
        if (pN == pM) return
        if (xp[pN] < xp[pM]) {
            val tmp = pN
            pN = pM
            pM = tmp
        }
        xp[pN] -= xp[pM]
        p[pN] = pM
    }

    fun add(n: Int, xp: Int) {
        val (p, _) = find(n)
        this.xp[p] += xp
    }

    fun get(n: Int): Int {
        val (_, xp) = find(n)
        return xp
    }
}

fun newGroups(size: Int): Groups {
    val xp = IntArray(size)
    val p = IntArray(size) { it }
    return Groups(p, xp)
}

fun main() {
    val reader = Scanner(System.`in`)

    val (playerCnt, queriesCnt) = reader.nextLine().split(" ").map { it.toInt() }

    val groups = newGroups(playerCnt)
    val results = mutableListOf<String>()

    repeat(queriesCnt) {
        val query = reader.nextLine().split(" ")
        val op = query[0]
        val n1 = query[1].toInt() - 1
        val n2 = if (query.size > 2) query[2].toInt() else 0

        when (op) {
            "get" -> results.add(groups.get(n1).toString())
            "join" -> groups.join(n1, n2 - 1)
            "add" -> groups.add(n1, n2)
        }
    }

    println(results.joinToString("\n"))
}
