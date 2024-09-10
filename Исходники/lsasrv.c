VOID
NTAPI
LsaIFree_LSAPR_POLICY_INFORMATION(IN POLICY_INFORMATION_CLASS InformationClass,
                                  IN PLSAPR_POLICY_INFORMATION PolicyInformation)
{
    if (PolicyInformation != NULL)
    {
        switch (InformationClass)
        {
            case PolicyAuditLogInformation:      /* 1 */
                break;

            case PolicyAuditEventsInformation:   /* 2 */
                if (PolicyInformation->PolicyAuditEventsInfo.EventAuditingOptions != NULL)
                    midl_user_free(PolicyInformation->PolicyAuditEventsInfo.EventAuditingOptions);
                break;

            case PolicyPrimaryDomainInformation: /* 3 */
                if (PolicyInformation->PolicyPrimaryDomInfo.Name.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyPrimaryDomInfo.Name.Buffer);

                if (PolicyInformation->PolicyPrimaryDomInfo.Sid != NULL)
                    midl_user_free(PolicyInformation->PolicyPrimaryDomInfo.Sid);
                break;

            case PolicyPdAccountInformation:     /* 4 */
                if (PolicyInformation->PolicyPdAccountInfo.Name.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyPdAccountInfo.Name.Buffer);
                break;

            case PolicyAccountDomainInformation: /* 5 */
                if (PolicyInformation->PolicyAccountDomainInfo.DomainName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyAccountDomainInfo.DomainName.Buffer);

                if (PolicyInformation->PolicyAccountDomainInfo.Sid != NULL)
                    midl_user_free(PolicyInformation->PolicyAccountDomainInfo.Sid);
                break;

            case PolicyLsaServerRoleInformation: /* 6 */
                break;

            case PolicyReplicaSourceInformation: /* 7 */
                if (PolicyInformation->PolicyReplicaSourceInfo.ReplicaSource.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyReplicaSourceInfo.ReplicaSource.Buffer);

                if (PolicyInformation->PolicyReplicaSourceInfo.ReplicaAccountName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyReplicaSourceInfo.ReplicaAccountName.Buffer);
                break;

            case PolicyDefaultQuotaInformation:  /* 8 */
                break;

            case PolicyModificationInformation:  /* 9 */
                break;

            case PolicyAuditFullSetInformation:  /* 10 (0xA) */
                break;

            case PolicyAuditFullQueryInformation: /* 11 (0xB) */
                break;

            case PolicyDnsDomainInformation:      /* 12 (0xC) */
                if (PolicyInformation->PolicyDnsDomainInfo.Name.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfo.Name.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfo.DnsDomainName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfo.DnsDomainName.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfo.DnsForestName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfo.DnsForestName.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfo.Sid != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfo.Sid);
                break;

            case PolicyDnsDomainInformationInt:   /* 13 (0xD) */
                if (PolicyInformation->PolicyDnsDomainInfoInt.Name.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfoInt.Name.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfoInt.DnsDomainName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfoInt.DnsDomainName.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfoInt.DnsForestName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfoInt.DnsForestName.Buffer);

                if (PolicyInformation->PolicyDnsDomainInfoInt.Sid != NULL)
                    midl_user_free(PolicyInformation->PolicyDnsDomainInfoInt.Sid);
                break;

            case PolicyLocalAccountDomainInformation: /* 14 (0xE) */
                if (PolicyInformation->PolicyLocalAccountDomainInfo.DomainName.Buffer != NULL)
                    midl_user_free(PolicyInformation->PolicyLocalAccountDomainInfo.DomainName.Buffer);

                if (PolicyInformation->PolicyLocalAccountDomainInfo.Sid != NULL)
                    midl_user_free(PolicyInformation->PolicyLocalAccountDomainInfo.Sid);
                break;

            default:
                ERR("Invalid InformationClass: %lu\n", InformationClass);
                break;
        }

        midl_user_free(PolicyInformation);
    }
}