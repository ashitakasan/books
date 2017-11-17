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

$$
\frac{\partial E(\textbf{w})}{\partial \textbf{w}} = \sum\_{n=1}^N\\{y(x\_n, \boldsymbol{w}) - t\_n\\} \cdot \frac{\partial y(x\_n, \boldsymbol{w})}{\partial \textbf{w}} + \lambda \textbf{w}
$$
$$
\frac{\partial y(x\_n, \boldsymbol{w})}{\partial \textbf{w}} = \frac{\partial \textbf{w}^T\textbf{x}}{\partial \textbf{w}} = \textbf{x} \\\\
\frac{\partial E(\textbf{w})}{\partial \textbf{w}} = \sum\_{n=1}^N{\sum\_{n=1}^M{x\_n^jw\_j}} \cdot x\_n^i - \sum\_{n=1}^N{t\_nx\_n^i} + \lambda \textbf{w}
$$
When E(w) got the Minimize error function, we'll have:
$$ \frac{\partial E(\textbf{w})}{\partial \textbf{w}} = 0 $$
$$ \sum\_{j=0}^M{\sum\_{n=1}^N{(x\_n)^{i+j}}w\_j} = \sum\_{n=1}^N{x\_n^i} \cdot t\_n + \lambda \textbf{w} $$
$$ \sum\_{j=0}^M{A\_{ij}w\_j} = T\_i + \lambda \textbf{w} $$
$$ among\ them: A_{ij} = \sum\_{n=1}^N{(x\_n)^{i+j}}, T\_i = \sum\_{n=1}^N{(x\_n)^i}t\_n $$

## 1.3
let p(A) = p(apple), p(O) = p(orange), p(L) = p(lime);

- p(A) = p(r) * (A | r) + P(b) * p(A | b) + p(g) * p(A | g) = 0.34;

- p(O) = p(r) * (O | r) + P(b) * p(O | b) + p(g) * p(O | g) = 0.36, p(g) = 0.6,  
	so p(g | O) = p(O | g) * p(g) / p(O) = 0.5

## 1.4
$$ p\_y(y) = p\_x(x)\|\frac{dx}{dy}\| = p\_x(g(y))\|g\prime(y)\| \tag{1.27} $$
$$ p\_y(y) = p\_x(g(y))sg\prime(y); s \in = \\{-1,+1\\} $$
$$ p\_y\prime(y) = sp\_x\prime(g(y))g\prime(y) + sp\_x(g(y))g\prime\prime(y) $$
$$ when: \ x = \widehat x; p\_x\prime(\widehat x) = p\_x\prime(g(\widehat y)) = 0 $$
$$ so: \ p\_y\prime(y) = sp\_x(g(y))g\prime\prime(y) $$
if x = g(y) is linear transformation, then:
$$ g\prime\prime(y) = 0 ; \ p\_y\prime(y) = 0 $$
$$ y = \widehat y; \ \widehat x = g(\widehat y) $$
but if not linear transformation, then:
$$ g\prime\prime(y) \ne 0 $$
$$ \widehat x \ne g(\widehat y) $$

## 1.5
$$ var[f] = \mathbb E[(f(x) - \mathbb E[f(x)])^2] \tag{1.38} $$
$$
\eqalignno{
var[f] &= \mathbb E[f(x)^2 + \mathbb E[f(x)]^2 - 2f(x) \cdot \mathbb E[f(x)]] \cr
&= \mathbb E[f(x)^2] + \mathbb E[\mathbb E[f(x)]^2] - \mathbb E[2f(x) \cdot \mathbb E[f(x)]]] \cr
&= \mathbb E[f(x)^2] + \mathbb E[f(x)]^2 - 2\mathbb E[f(x)] \cdot \mathbb E[f(x)] \cr
}
$$
$$ var[f] = E[f(x)^2] - \mathbb E[f(x)]^2 \tag{1.39} $$

## 1.6
if x and y are independency:
$$
\eqalignno{
p(x, y) &= p(x)p(y) \cr
E\_{x,y}[xy] &= \sum\_{x,y}{p(x,y)xy} = \sum\_{x}{p(x)} \cdot \sum\_{y}{p(y)} \cr
E\_{x,y}[xy] &= E\_x[x] \cdot E\_x[y] \cr
cov[x,y] &= E\_{x,y}[xy] - E\_x[x] \cdot E\_x[y] = 0
}
$$

## 1.7
$$
x = r \cos \theta \\\\
y = r \sin \theta
$$
$$
\eqalignno{
\frac{\partial x \partial y}{\partial r \partial \theta} &= 
\begin{vmatrix}
\frac{\partial x}{\partial r} & \frac{\partial x}{\partial \theta} \cr
\frac{\partial y}{\partial r} & \frac{\partial y}{\partial \theta}
\end{vmatrix} \cr
&= \begin{vmatrix}
\cos \theta & -r \sin \theta \cr
\sin \theta & r \cos \theta
\end{vmatrix} \cr
&= r
}
$$
$$
\eqalignno{
I^2 &= \int\_0^{2\pi}\int\_0^{\infty}\exp (-\frac{r^2}{2\sigma^2}) \ drd\theta \cr
&= \pi \int\_0^{\infty}\exp (-\frac{u}{2\sigma^2}) \ du \cr
&= \pi \left[\exp (-\frac{u}{2\sigma^2})(-2\sigma^2) \right] 
\begin{array}{|lr}
\infty \cr
0
\end{array} \cr
&= 2\pi \sigma^2
}
$$
$$ I = (2\pi \sigma^2)^{\frac 12} $$
$$
\eqalignno{
\int\_{-\infty}^{+\infty} \mathcal{N}(\mu, \sigma^2) &= \int\_{-\infty}^{+\infty} 
\frac{1}{{\sigma \sqrt{2\pi}}} \exp (-\frac{(x-\mu)^2}{2\sigma^2}) \ d(x-\mu) \cr
&= \frac{1}{{\sigma \sqrt{2\pi}}} (2\pi \sigma^2)^{\frac 12} \cr
&= 1
}
$$

## 1.8
ax^{2} + by^{2} + c = 0


<br><br><br>

---
__View formulas on github pages with chrome extension [Github with MathJax](https://chrome.google.com/webstore/detail/github-with-mathjax/ioemnmodlmafdkllaclgeombjnmnbima) or download and view at localhost__
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/MathJax.js?config=TeX-MML-AM_CHTML">
</script>










