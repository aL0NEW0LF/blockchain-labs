Developed on Ubuntu 22.04

### To test C code:

```shell
git clone https://github.com/aL0NEW0LF/blockchain-labs.git
```

```shell
cd blockchain-labs/c
```

```shell
mkdir obj
```

**to compile and run the hash test:**

```shell
make hash_test
```

```shell
./hash_test
```

**to compile and run the blockchain test:**

```shell
make blockchain_test
```

```shell
./blockchain_test
```

**To clean the project:**

```shell
make clean
```

### To test the twitter Dapp:

Fist, you need compile and deploy the smart contract using remix IDE.

Then to start the hardhat server:

```shell
cd blockchain-labs/hhproject/chain
```

```shell
pnpm install
```

```shell
npx hardhat node
```

Then to start the frontend:

```shell
cd blockchain-labs/hhproject/webapp
```

And start a python server:

```shell
python3 -m http.server
```

Then open the browser and go to `http://localhost:8000/social_media.html`

# References

- B-Con, “Github - b-con/crypto-algorithms: Basic implementations of standard cryptography algorithms, like
  aes and sha-1.” [Online]. Available: https://github.com/B-Con/crypto-algorithms.

- Adam-Mcdaniel, “Github - adam-mcdaniel/rsa: An rsa implementation in c, using arbitrarily large integers.”
  [Online]. Available: https://github.com/adam-mcdaniel/rsa

- Adam-Mcdaniel, “Github - adam-mcdaniel/bigint: A library for arbitrarily large integers, written in c.” [Online].
  Available: https://github.com/adam-mcdaniel/bigint
