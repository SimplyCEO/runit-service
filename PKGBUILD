# Maintainer J. Simplício <simplyceo.developer@gmail.com)

pkgname=runit-service
pkgdesc="A custom tool to manage runit services."
pkgver=a0.2.1
pkgrel=1
replaces=('runit-service')
arch=('x86_64' 'i686' 'aarch64' 'armv7h')
url='https://gitlab.com/SimplyCEO/runit-service'
license=('GPL-2.0-or-later')
depends=('make' 'runit')
optdepends=('gcc' 'clang' 'tcc')
source=("${pkgname}-${pkgver}.tar.gz::https://gitlab.com/SimplyCEO/runit-service/-/archive/master/runit-service-master.tar.gz")
sha256sums=('c5dc8c4a72fdb711fbd60a1997ea6bf1b896853607cea921a180403aa7abedc4')

build()
{
  cd "${srcdir}/${pkgname}-master"

  make
}

package()
{
  cd "${srcdir}/${pkgname}-master"

  install -Dm755 bin/${pkgname} "${pkgdir}/usr/bin/${pkgname}"
  install -Dm755 service/runit-journal/run "${pkgdir}/etc/runit/sv/runit-journal/run"

  make clean
}

