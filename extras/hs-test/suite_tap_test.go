package main

import (
	"time"
)

type TapSuite struct {
	HstSuite
}

func (s *TapSuite) SetupSuite() {
	time.Sleep(1 * time.Second)
	s.HstSuite.SetupSuite()
	s.configureNetworkTopology("tap")
}
