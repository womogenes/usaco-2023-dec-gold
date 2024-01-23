# Do a topological sort, then iterate backwards
# from pprint import pprint

N, M = map(int, input().split())

adj = [[] for _ in range(N)]
in_adj = [[] for _ in range(N)]

h = 0
for _ in range(M):
    a, b, l = map(int, input().split())
    h += (a * b * l) % (10**9 + 7)
    adj[a-1].append((b-1, l))
    in_adj[b-1].append(a-1)


# Do a topo sort
outdeg = [len(adj[node]) for node in range(N)]
stack = [node for node in range(N) if outdeg[node] == 0]
toposort = []
while len(stack) > 0:
    top = stack.pop()
    toposort.append(top)
    for pred in in_adj[top]:  # Predecessor
        if outdeg[pred] == 0:
            continue
        outdeg[pred] -= 1
        if outdeg[pred] == 0:
            stack.append(pred)

# Do the DP
if h % 2 == 1:
    dp = [None] * N
    for node in toposort:
        if len(adj[node]) == 0:
            dp[node] = (0, 0, 0, 0)
            continue

        options = [(1 + dp[nbr][0], -l, -l * pow(1.01, dp[nbr][0]) +
                    dp[nbr][2], -l + dp[nbr][3]) for nbr, l in adj[node]]
        chosen = max(options)
        dp[node] = chosen

    for i, val in enumerate(dp):
        print(val[0], -val[3])

else:
    dp = [None] * N
    for node in toposort:
        if len(adj[node]) == 0:
            dp[node] = (0, 0, 0)
            continue

        options = [(1 + dp[nbr][0], -l, -l + dp[nbr][2])
                   for nbr, l in adj[node]]
        chosen = max(options)
        dp[node] = chosen

    for i, val in enumerate(dp):
        print(val[0], -val[2])
