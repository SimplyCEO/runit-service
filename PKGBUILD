# Maintainer J. Simplício <simplyceo.developer@gmail.com)

pkgname=runit-service
pkgdesc="A custom tool to manage runit services."
pkgver=a0.2.0
pkgrel=1
replaces=('runit-service')
arch=('x86_64' 'i686' 'aarch64' 'armv7h')
url='https://gitlab.com/SimplyCEO/runit-service'
license=('GPL-2.0-or-later')
depends=('make' 'runit')
optdepends=('gcc' 'clang' 'tcc')
source=("${pkgname}-${pkgver}.tar.gz::https://gitlab.com/SimplyCEO/runit-service/-/archive/master/runit-service-master.tar.gz")
sha256sums=('c274aae3e138facaea5ad46f152f1a1904941e27511d940968eb466b7e1f55e2')

build()
{
  cd "${srcdir}/${pkgname}-master"

  make
}

package()
{
  cd "${srcdir}/${pkgname}-master"

  install -Dm755 bin/${pkgname} "${pkgdir}/usr/bin/${pkgname}"

  make clean
}

