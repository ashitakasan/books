## 1.1

$$ y(x, \boldsymbol{w}) = w\_0 + w\_1x + w\_2x^2 + \cdots + w\_Mx^M = \sum\_{j=0}^M{w\_jx^j} \tag{1.1} $$
$$ E(\boldsymbol{w}) = \frac{1}{2}\sum_{n=1}^N\\{y(x\_n, \boldsymbol{w}) - t\_n\\}^2 \tag{1.2} $$

When E(w) got the Minimize error function, we'll have: $$ t_n = y(x\_n, \boldsymbol{w}) $$ so:

$$ 
\eqalignno{
\sum\_{j=0}^M{x\_n^jw\_j} &= t\_n \cr
\sum\_{n=1}^N{x\_n^i} \cdot \sum\_{j=0}^M{x\_n^jw\_j} &= \sum\_{n=1}^N{x\_n^i} \cdot t\_n \cr
\sum\_{j=0}^M{\sum\_{n=1}^N{(x\_n)^{i+j}}w\_j} &= \sum\_{n=1}^N{x\_n^i} \cdot t\_n \cr
\sum\_{j=0}^M{A\_{ij}w\_j} &= T\_i &(1.122) \cr
among\ them: A_{ij} = \sum\_{n=1}^N{(x\_n)^{i+j}}, T\_i &= \sum\_{n=1}^N{(x\_n)^i}t\_n
}
$$

## 1.2
$$ E(\textbf{w}) = \frac{1}{2}\sum_{n=1}^N\\{y(x\_n, \boldsymbol{w}) - t\_n\\}^2 + \frac{\lambda}{2}\\|\textbf{w}\\|^2 \tag{1.4} $$
$$ \sum\_{j=0}^M{A\_{ij}w\_j} = T\_i  $$




<br><br><br>

-----
__View formulas on github pages with chrome extension [Github with MathJax](https://chrome.google.com/webstore/detail/github-with-mathjax/ioemnmodlmafdkllaclgeombjnmnbima) or download and view at localhost__
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
