# Copyright (c) 2023 Luiz Carlos Gili
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# LBUILD = python3 ../../lbuild
LBUILD = $(shell which lbuild)
# SCONS = python3 `which scons`
SCONS = scons

define compile-test
	@$(RM) -r ../build/generated-unittest/$(1)
	$(LBUILD) -p ../build/generated-unittest/$(1) -c config/$(1).xml $(3) \
			  -C ../build/generated-unittest/$(1) build 
	$(SCONS) -C ../build/generated-unittest/$(1) $(2)
endef
define run-test
	$(call compile-test,$(1),$(2) program,$(3))
endef



run-hosted-linux:
	$(call compile-test,hosted,run,-D":target=hosted-linux")
