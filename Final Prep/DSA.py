import hashlib

# Given parameters
p = 59
q = 29
alpha = 3
d = 7
kE = 10
x_hash = 26

# Function to calculate modular exponentiation
def mod_exp(base, exponent, mod):
    result = 1
    base = base % mod
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % mod
        exponent = exponent // 2
        base = (base * base) % mod
    return result

# Function to calculate modular inverse
def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

#Key Pair Generation
y = mod_exp(alpha, d, p)
print(f"Key (y): {y}")

beta = mod_exp(alpha, d, p)
print(f"Beta = alpha^d mod p = ({alpha}^{d}) mod {p} = {beta} mod {p}")

print(f"Private Key = d = {d}")
print(f"Public Key = (p,q,alpha,beta) = ({p},{q},{alpha},{beta})")

# Signature Generation
r = mod_exp(alpha, kE, p) % q
print(f"r = (alpha^(kE)mod p) mod q = ({alpha} ^ {kE} mod {p}) mod {q} = {r} mod {q}")
j = mod_inverse(kE, q)
print(f"kE^-1 = {kE}^(-1) = {j}")
s = ((x_hash + d * r) * j) % q
print(f"s = (h(x) + d * r)* kE^(-1) mod q = ({x_hash} + {d}*{r}) * {j} mod {q} = {s} mod {q}")

print("---------")
# Signature Verification
w = mod_inverse(s, q)
print(f"W = s^(-1) mod q = {s}^(-1) = {w} mod {q}")
u1 = (w * x_hash) % q
print(f"u1 = (w * h(x)) mod q = {w} * {x_hash} mod {q} = {u1} mod {q}")
u2 = (w * r) % q
print(f"u2 = (w * r) mod q = {w} * {r} mod {q} = {u2} mod {q}")
print("------------")
v = (mod_exp(alpha, u1, p) * mod_exp(y, u2, p)) % q
print(f"v = (alpha^u1 * beta^u2 mod p) mod q = ({alpha}^{u1} * {beta}^{u2} mod p) mod q = {v} mod {q}")

# Check if the signature is valid
if v == r:
    print(f"Because {v} mod {q} == {r} mod {q} So Valid Signature")
else:
    print(f"Because {v} mod {q} different {r} mod {q} So Invalid Signature")
