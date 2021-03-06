<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="html" encoding="windows-1250"/>

	<xsl:template match="/report">
		<html>
			<head>
				<title>Time Sheet Report</title>
				<style>
					body { background-color:#ffffff; }
					td { font-family: arial; font-size:9pt; }
					td.header { border-bottom:1px solid black; padding:3px; }
					td.footer { border-top:1px solid black; padding:3px; }
					td.cellBorderTop { border-top:1px solid #777777; }
					td.cell { padding:3px; border-top:1px solid #777777; }
					td.date { border-right:1px solid #777777; width:10em; }
					td.dayDuration { border-left:1px solid #777777; width:5em; text-align:right; }
					td.activity { white-space:nowrap; }
					td.description { }
					td.time { white-space:nowrap; text-align:right; }
				</style>
			</head>
			<body>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr valign="middle">
					<td align="left" ><img height="30px" src="logo.gif"/></td>
					<td align="center" style="font-size:20pt;">Time Sheet</td>
					<td align="right">
						<table border="0" cellspacing="0" cellpadding="2">
						<tr valign="top">
							<td align="right">Contractor:</td>
							<td align="left">xxx</td>
						</tr>
						<tr valign="top">
							<td align="right">Period:</td>
							<td align="left">
								<xsl:value-of select="period/from"/>
								to
								<xsl:value-of select="period/to"/>
							</td>
						</tr>
						</table>
					</td>
				</tr>
				</table>
				<xsl:apply-templates select="days" />
			</body>
		</html>
	</xsl:template>

	<xsl:template match="days">
		<table width="100%" border="0" cellspacing="0" cellpadding="0" style="border:1px solid black; margin-top:8px;">
		<tr valign='top' style="background-color:#dddddd;">
		  <td class="header date">Date</td>
		  <td class="header" colspan="3">Tasks</td>
		  <td class="header dayDuration">Days</td>
		</tr>
		<xsl:apply-templates select="day"/>
		<tr valign="top" style="background-color:#dddddd;">
			<td class="footer date" valign="middle">Total</td>
			<td class="footer" colspan="3"></td>
			<td class="footer dayDuration">
				<b><xsl:value-of select="/report/total"/> days</b>
			</td>
		</tr>
		</table>
	</xsl:template>

	<xsl:template match="day">
		<tr valign="top">
  			<td class="cell date">
  				<xsl:value-of select="date"/>
  			</td>
			<td class="cell activity">
				<xsl:for-each select="tasks/task">
					<xsl:value-of select="project"/> - <xsl:value-of select="activity"/><br/>
				</xsl:for-each>
			</td>
			<td class="cell description">
				<xsl:for-each select="tasks/task">
					<xsl:value-of select="description"/><br/>
				</xsl:for-each>
			</td>
			<td class="cell time">
				<xsl:for-each select="tasks/task">
					<xsl:value-of select="duration"/><br/>
				</xsl:for-each>
			</td>
			<td class="cell dayDuration">
				<xsl:value-of select="duration"/>
			</td>
		</tr>
	</xsl:template>

</xsl:stylesheet>
