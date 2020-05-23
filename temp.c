

int max(int a, int b) {
  if(a > b) return a;
  return b;
}

int coin_row(int[] C, int n) {
  int F[n+1], i;
  F[0] = 0; F[1] = C[1];

  for(i = 2;i<=n;i++) {
    F[i] = max(C[i] + F[i-2], F[i-1]);
  }

  return F[n];
}

