import java.util.Scanner


const val maxZerg = 1000003

class Chats(val size: Long, var zerg: Long, val p: LongArray, val msgAll: LongArray, val msgReaded: LongArray) {
    fun find(n: Long): Pair<Long, Long> {
        if (p[n.toInt()] == n) {
            return n to msgAll[n.toInt()]
        }
        val (chatParent, chatMsg) = find(p[n.toInt()])
        p[n.toInt()] = chatParent
        msgAll[n.toInt()] += chatMsg - msgAll[p[n.toInt()].toInt()]
        return p[n.toInt()] to msgAll[n.toInt()] + msgAll[p[n.toInt()].toInt()]
    }

    fun merge(n: Long, m: Long) {
        var (pN, _) = find((n + zerg) % size)
        var (pM, _) = find((m + zerg) % size)
        if (pN == pM) return
        zerg = (13 * zerg + 11) % maxZerg
        if (msgAll[pN.toInt()] < msgAll[pM.toInt()]) {
            val tmp = pN
            pN = pM
            pM = tmp
        }
        msgAll[pN.toInt()] -= msgAll[pM.toInt()]
        p[pN.toInt()] = pM
    }

    fun sendMsg(n: Long) {
        val (p, _) = find((n + zerg) % size)
        msgAll[p.toInt()] = msgAll[p.toInt()] + 1
        zerg = (30 * zerg + 239) % maxZerg
    }

    fun readMsg(n: Long): Long {
        val (_, msg) = find((n + zerg) % size)
        val newMsg = msg - msgReaded[(n + zerg).toInt() % size.toInt()]
        msgReaded[(n + zerg).toInt() % size.toInt()] += newMsg
        zerg = (100500 * zerg + newMsg) % maxZerg
        return newMsg
    }
}

fun newChats(size: Int): Chats {
    val msgAll = LongArray(size)
    val msgReaded = LongArray(size)
    val p = LongArray(size) { it.toLong() }
    return Chats(size.toLong(), 0, p, msgAll, msgReaded)
}

fun main() {
    val reader = Scanner(System.`in`)

    val (usersCnt, actionsCnt) = reader.nextLine().split(" ").map { it.toInt() }

    val chats = newChats(usersCnt)
    val results = mutableListOf<String>()

    for (k in 0..<actionsCnt) {
        val action = reader.nextLine().split(" ")
        val act = action[0].toInt()
        val i = action[1].toLong()
        val j = if (action.size > 2) action[2].toLong() else 0L

        when (act) {
            1 -> chats.sendMsg(i)
            2 -> chats.merge(i, j)
            3 -> results.add(chats.readMsg(i).toString())
        }
    }

    println(results.joinToString("\n"))
}
