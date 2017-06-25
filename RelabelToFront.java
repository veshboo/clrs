/*
  Maxflow network - relabel to front algorithm
  @usage see main()
*/

import java.util.Map;
import java.util.HashMap;

import java.util.Iterator;
import java.util.List;
import java.util.LinkedList;

public class RelabelToFront {

    static class Vert {
        String id;
        int e;
        int h;
        List<Vert> N = new LinkedList<>();
        Iterator<Vert> it;
        Vert(String id) { this.id = id; }
        @Override public String toString() { return "{id=" + id + ", e=" + e + ", h=" + h + "}"; }
    }

    static class Edge {
        Vert from;
        Vert to;
        int c;
        int f;
        Edge(Vert from, Vert to, int c) { this.from = from; this.to = to; this.c = c; }
        @Override public String toString() { return "{from=" + from.id + ", to=" + to.id + ", e=" + c + ", f=" + f + "}"; }
    }

    Map<String, Vert> V = new HashMap<>();
    Map<Vert, Map<Vert, Edge>> A = new HashMap<>();

    public RelabelToFront() {}

    public void addEdge(String from, String to, int c) {
        Vert u = addVert(from);
        Vert v = addVert(to);
        A.get(u).put(v, new Edge(u, v, c));
    }

    Vert addVert(String id) {
        if (V.containsKey(id)) {
            return V.get(id);
        } else {
            Vert v = new Vert(id);
            V.put(id, v);
            A.put(v, new HashMap<>());
            return v;
        }
    }

    Edge getEdge(Vert u, Vert v) {
        return A.get(u).get(v);
    }

    // residual capacity
    int cf(Vert u, Vert v) {
        Edge uv = getEdge(u, v);
        if (uv != null) {
            return uv.c - uv.f;
        } else {
            Edge vu = getEdge(v, u);
            if (vu != null) {
                return vu.f;
            } else {
                return 0;
            }
        }
    }

    // u.e > 0 && cf(u, v) > 0 && u.h = v.h + 1 when invoked
    void push(Vert u, Vert v) {
        int amount = Math.min(u.e, cf(u, v));
        Edge uv = getEdge(u, v);
        if (uv != null) {
            uv.f += amount;
        } else {
            Edge vu = getEdge(v, u);
            vu.f -= amount;
        }
        u.e -= amount;
        v.e += amount;
    }

    void relabel(Vert u) {
        int minH = Integer.MAX_VALUE;
        // just checking Adj[u] is not enough,
        // checking all v in V is too much enough,
        // checking only u's neighbors is necessary enough.
        // (A small optimization for the CLRS's RELABEL procedure
        // which is for GENERIC PUSH-RELABEL algorithm)
        for (Vert v : u.N) {
            // u.N does not include u itself.
            // Even if it does, when v is u, cf(u, v) == cf(v, v) == 0,
            // thus it will be skipped safely.
            // (or height will always increase by 1, tediously)
            if (cf(u, v) > 0) {
                minH = Math.min(minH, v.h);
            }
        }
        u.h = minH + 1;
    }

    void buildNeighborList() {
        for (Vert u : V.values()) {
            for (Vert v : A.get(u).keySet()) {
                u.N.add(v);
                v.N.add(u);
            }
        }
    }

    void initializePreflow(Vert s) {
        for (Vert v : V.values()) {
            v.e = 0;
            v.h = 0;
        }
        for (Map<Vert, Edge>adj_u : A.values()) {
            for (Edge uv : adj_u.values()) {
                uv.f = 0;
            }
        }
        s.h = V.size();
        for (Vert v : A.get(s).keySet()) {
            Edge sv = getEdge(s, v);
            sv.f = sv.c;
            s.e -= sv.c;
            v.e += sv.c;
        }
    }

    void discharge(Vert u) {
        while (u.e > 0) {
            if (u.it.hasNext() == false) {
                relabel(u);
                u.it = u.N.iterator();
            } else {
                Vert v = u.it.next();
                if (cf(u, v) > 0 && u.h == v.h + 1) {
                    push(u, v);
                }
            }
        }
    }

    void relabelToFront(Vert s, Vert t) {
        initializePreflow(s);
        LinkedList<Vert> L = new LinkedList<>();
        for (Vert u : V.values()) {
            if (u != s && u != t) {
                L.add(u);
                u.it = u.N.iterator();
            }
        }
        Iterator<Vert> it = L.iterator();
        while (it.hasNext()) {
            Vert u = it.next();
            int originalHeight = u.h;
            discharge(u);
            if (u.h > originalHeight) {
                it.remove();
                L.addFirst(u);
                it = L.iterator();
                it.next();
            }
        }
    }

    public void run(String s, String t) {
        buildNeighborList();
        relabelToFront(V.get(s), V.get(t));
    }

    public void print() {
        System.out.println("== V ==");
        for (Vert v : V.values()) {
            System.out.println(v);
        }
        System.out.println("== A ==");
        for (Vert u : V.values()) {
            for (Edge uv : A.get(u).values()) {
                System.out.println(uv);
            }
        }
    }

    public static void main(String[] args) {
        // Example from CLRS
        RelabelToFront flowNet = new RelabelToFront();
        flowNet.addEdge("s", "x", 12);
        flowNet.addEdge("s", "y", 14);
        flowNet.addEdge("x", "y", 5);
        flowNet.addEdge("x", "t", 16);
        flowNet.addEdge("y", "z", 8);
        flowNet.addEdge("z", "x", 7);
        flowNet.addEdge("z", "t", 10);
        flowNet.run("s", "t");
        flowNet.print();
    }
}
