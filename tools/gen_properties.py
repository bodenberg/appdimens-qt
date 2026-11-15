"""Generates the QML factor properties of AppDimens::Scope (moc cannot expand macros)."""
import os

PREFIX = [("", "AD_SCALED"), ("a", "AD_AUTO"), ("p", "AD_PERCENT"), ("pw", "AD_POWER"), ("f", "AD_FLUID"),
          ("i", "AD_INTERPOLATED"), ("log", "AD_LOGARITHMIC"), ("dg", "AD_DIAGONAL"), ("pr", "AD_PERIMETER"),
          ("ft", "AD_FIT"), ("fl", "AD_FILL"), ("d", "AD_DENSITY")]
AX = [("s", "AD_VAR_S"), ("h", "AD_VAR_H"), ("w", "AD_VAR_W")]
props = []  # (name, strategy, variant, flags, sp)
for p, s in PREFIX:
    for a, v in AX:
        props.append((p + a + "dp", s, v, 0, False))
        props.append((p + a + "sp", s, v, 0, True))
        props.append((p + a + "dpa", s, v, 1, False))
        props.append((p + a + "dpi", s, v, 2, False))
for a, v in AX:
    props.append((a + "em", "AD_SCALED", v, 0, False))
    props.append(("a" + a + "em", "AD_AUTO", v, 0, False))
    props.append((a + "spa", "AD_SCALED", v, 1, True))
    props.append(("a" + a + "spa", "AD_AUTO", v, 1, True))
for name, v in [("sdpPh", "AD_VAR_S_PH"), ("sdpLh", "AD_VAR_S_LH"), ("sdpPw", "AD_VAR_S_PW"), ("sdpLw", "AD_VAR_S_LW"),
                ("hdpLw", "AD_VAR_H_LW"), ("hdpPw", "AD_VAR_H_PW"), ("wdpLh", "AD_VAR_W_LH"), ("wdpPh", "AD_VAR_W_PH")]:
    props.append((name, "AD_SCALED", v, 0, False))
    props.append(("a" + name, "AD_AUTO", v, 0, False))
decl = []
for n, s, v, f, sp in props:
    decl.append("    Q_PROPERTY(qreal %s READ %s NOTIFY changed)" % (n, n))
decl.append("public:  // factor getters: size = value × factor")
for n, s, v, f, sp in props:
    expr = "m_m.table[%s][AD_SLOT(%s, %d)]" % (s, v, f) + (" * m_m.in.font_scale" if sp else "")
    decl.append("    qreal %s() const { return %s; }" % (n, expr))
out = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "include", "appdimens", "appdimens_qt.hpp")
src = open(out).read()
a = src.index("    // <generated>")
a = src.index("\n", a) + 1
b = src.index("    // </generated>")
open(out, "w").write(src[:a] + "\n".join(decl) + "\n" + src[b:])
print(out, len(props), "properties")
