/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import { LocaleData } from '../localeContext'

export const Container = styled.div`
  padding: 7px 15px 28px;
  border-top: solid 1px ${p => p.theme.color.separatorLine};
  border-bottom: solid 1px ${p => p.theme.color.separatorLine};

  table {
    border-collapse: collapse;
    width: 100%;

    td, th {
      padding: 0;
      text-align: left;
      vertical-align: top;
      line-height: 22px;
      min-width: 96px;
    }

    th {
      color: ${p => p.theme.palette.blurple600};
      font-weight: 500;
      padding-top: 4px;
    }

    td {
      padding-top: 8px;
    }
  }
`

export const Description = styled.div`
  padding-right: 4em;
`

export const BatAmount = styled.span<{ locale: LocaleData }>`
  font-size: 18px;
  font-weight: 500;

  &::after {
    content: "${p => p.locale.get('bat')}";
    padding-left: 5px;
    font-size: 16px;
    font-weight: normal;
  }
`

export const ExchangeAmount = styled.span`
  display: block;
  color: ${p => p.theme.palette.grey600};
`
