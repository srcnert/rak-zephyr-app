import argparse
import os
from pathlib import Path
import subprocess

from west import log
from west.commands import WestCommand, CommandError
from west.manifest import MANIFEST_PROJECT_INDEX
from west.app.project import _ProjectCommand

class PatchRak(_ProjectCommand):
	def __init__(self):
		super().__init__(
			'patch_rak',
			'patch_rak west subprojects',
			'Runs "git apply patches/<project>/" on each of the specified projects.')

	def do_add_parser(self, parser_adder):
		parser = self._parser(parser_adder)
		parser.add_argument('projects', metavar='PROJECT', nargs='*',
							help='''projects (by name or path) to operate on;
							defaults to active cloned projects''')

		parser.add_argument('--revert',
					action='store_true',
					help='Check verbose status')

		return parser

	def do_run(self, args, ignored):
		manifest_project = self.manifest.projects[MANIFEST_PROJECT_INDEX]
		manifest_project_path = Path(manifest_project.abspath)
		manifest_project_path = manifest_project_path / "zephyr"
		failed = []
		for project in self._cloned_projects(args):
			patches = []

			try:
				patches_dirs = manifest_project.userdata['patches_dirs']
			except (TypeError, AttributeError, KeyError):
				patches_dirs = ['patches']

			for patches_dir in patches_dirs:
				patches_path = manifest_project_path / patches_dir / project.name
				if not patches_path.exists():
					continue

				patches += sorted(filter(Path.is_file, patches_path.glob('*.patch')))

			if not patches:
				continue

			log.banner(f'patching {project.name_and_path}):')

			for patch in patches:
				if args.revert == False:
					cmd = 'apply'
				else:
					cmd = 'apply -R'
				try:
					log.inf(f'git {cmd} {patch.relative_to(manifest_project_path)}')
					project.git(cmd.split() + [str(patch)])
				except subprocess.CalledProcessError:
					failed.append(project)
					continue
		self._handle_failed(args, failed)
