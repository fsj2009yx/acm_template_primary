num = sqrt(n);
for (int i = 1; i <= num; i++)
    st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
ed[num] = n;
for (int i = 1; i <= num; i++)
{
    for (int j = st[i]; j <= ed[i]; j++)
    {
        belong[j] = i;
    }
    size[i] = ed[i] - st[i] + 1;
}